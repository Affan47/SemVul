mupdate_deactivate(mupdate_handle *handle,
		       const char *mailbox, const char *server)
{
    int ret;
    enum mupdate_cmd_response response;
    const char *p;

    if (!handle) return MUPDATE_BADPARAM;
    if (!mailbox || !server) return MUPDATE_BADPARAM;
    if (!handle->saslcompleted) return MUPDATE_NOAUTH;


    if ((p = strchr(server, '!')) && strchr(p+1, '!')) return MUPDATE_BADPARAM;

    if (config_mupdate_config == IMAP_ENUM_MUPDATE_CONFIG_REPLICATED) {

	if (p) server = p + 1;
    }

    prot_printf(handle->conn->out,
		"X%u DEACTIVATE {" SIZE_T_FMT "+}\r\n%s {" SIZE_T_FMT "+}\r\n%s\r\n",
		handle->tagn++, strlen(mailbox), mailbox,
		strlen(server), server);

    ret = mupdate_scarf(handle, mupdate_scarf_one, NULL, 1, &response);
    if (ret) {
	return ret;
    } else if (response != MUPDATE_OK) {
	return MUPDATE_FAIL_RESERVE;
    } else {
	return 0;
    }
}
