pic_read_cb(gint sk, gpointer user_data)
{
    gint     n, len;
    gchar    sipmsg[BUF_LENGTH];
    gchar   *code, *pos;
    guchar  *pic;
    gint     piclen;
    xmlnode *root;
    xmlnode *node;

    fetion_account *ac = (fetion_account*)user_data;

    len    = ac->buffer ? strlen(ac->buffer) : 0;

    if((n = recv(sk, sipmsg, strlen(sipmsg), 0)) == -1) {
        return -1;
    }

    sipmsg[n] = 0;

    if(n == 0) {
           g_source_remove(ac->source);
        ac->source = 0;
        close(sk);

        if(! ac->buffer) {
            return 0;
        }

        hybrid_debug_info("fetion", "read message resp:\n%s", ac->buffer);

        if (200 != hybrid_get_http_code(ac->buffer)) {
            goto read_pic_err;
        }

        if(!(pos = strstr(ac->buffer, "\r\n\r\n"))) {
            goto read_pic_err;
        }

        pos += 4;

        if (!(root = xmlnode_root(pos, strlen(pos)))) {
            goto read_pic_err;
        }

        if (!(node = xmlnode_find(root, "pic-certificate"))) {
            xmlnode_free(root);
            goto read_pic_err;
        }

        if (!xmlnode_has_prop(node, "id") || !xmlnode_has_prop(node, "pic")) {
            xmlnode_free(root);
            goto read_pic_err;
        }

        ac->verification->guid = xmlnode_prop(node, "id");
        code                   = xmlnode_prop(node, "pic");

        pic = hybrid_base64_decode(code, &piclen);

        hybrid_confirm_window_create(ac->account, pic, piclen,
                                     pic_code_ok_cb, pic_code_cancel_cb, ac);

        g_free(code);
        g_free(pic);
        xmlnode_free(root);
        g_free(ac->buffer);
        ac->buffer = (gchar*)0;

        return FALSE;
    }

    ac->buffer = (gchar*)realloc(ac->buffer, len + n + 1);
    memcpy(ac->buffer + len, sipmsg, n + 1);

    return TRUE;

 read_pic_err:
    hybrid_debug_error("fetion", "read pic code error.");

    g_free(ac->buffer);
    ac->buffer = (gchar *)0;

    hybrid_account_error_reason(ac->account, _("read pic code error."));
    return FALSE;
}
