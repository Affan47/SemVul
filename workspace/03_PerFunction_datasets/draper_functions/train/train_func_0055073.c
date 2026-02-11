buddy_get_info_cb(XmppStream *stream, xmlnode *root, XmppBuddy *buddy)
{
    xmlnode *node;
    gchar   *type;
    gchar   *photo_bin;
    guchar  *photo;
    gint     photo_len;

    if (xmlnode_has_prop(root, "type")) {
        type = xmlnode_prop(root, "type");

        if (g_strcmp0(type, "result") != 0) {

            hybrid_debug_error("xmpp", "get buddy info error.");
            g_free(type);

            return FALSE;
        }

        g_free(type);
    }

    if ((node = xmlnode_find(root, "PHOTO"))) {

        if ((node = xmlnode_find(root, "BINVAL"))) {

            photo_bin = xmlnode_content(node);


            photo = hybrid_base64_decode(photo_bin, &photo_len);


            hybrid_blist_set_buddy_icon(buddy->buddy, photo,
                                    photo_len, buddy->photo);
            g_free(photo_bin);
            g_free(photo);
        }
    }

    return TRUE;
}
