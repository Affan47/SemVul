display_message(struct transaction_t *txn,
			    const char *mboxname, uint32_t uid,
			    struct body *body, const char *msg_base)
{
    struct body toplevel;
    struct buf *buf = &txn->resp_body.payload;
    unsigned level = 0;


    txn->flags.te |= TE_CHUNKED;
    txn->resp_body.type = "text/html; charset=utf-8";


    if (txn->meth == METH_HEAD) {
	response_header(HTTP_OK, txn);
	return;
    }


    buf_reset(buf);
    buf_printf_markup(buf, level, HTML_DOCTYPE);
    buf_printf_markup(buf, level++, "<html>");
    buf_printf_markup(buf, level++, "<head>");
    buf_printf_markup(buf, level, "<title>%s:%u</title>",
		      mboxname, uid);
    buf_printf_markup(buf, --level, "</head>");
    buf_printf_markup(buf, level++, "<body>");


    buf_printf_markup(buf, level++, "<div align=center>");
    buf_printf_markup(buf, level,
		      "<a href=\"%s?uid=%u;section=0\" type=\"plain/text\">"
		      "[View message source]</a>",
		      txn->req_tgt.path, uid);
    buf_printf_markup(buf, --level, "</div>");
    buf_printf_markup(buf, level, "<hr>");

    write_body(HTTP_OK, txn, buf_cstring(buf), buf_len(buf));
    buf_reset(buf);


    memset(&toplevel, 0, sizeof(struct body));
    toplevel.type = "MESSAGE";
    toplevel.subtype = "RFC822";
    toplevel.subpart = body;

    display_part(txn, &toplevel, uid, "", msg_base, level);


    buf_printf_markup(buf, --level, "</body>");
    buf_printf_markup(buf, --level, "</html>");

    write_body(0, txn, buf_cstring(buf), buf_len(buf));


    write_body(0, txn, NULL, 0);
}
