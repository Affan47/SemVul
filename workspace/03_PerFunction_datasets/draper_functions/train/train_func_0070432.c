set_config_destroy(void)
{
	strcpy(accountcode, "");
	strcpy(language, "");
	strcpy(mohinterpret, "");
	strcpy(mohsuggest, "");
	trunkmaxsize = MAX_TRUNKDATA;
	amaflags = 0;
	delayreject = 0;
	ast_clear_flag64((&globalflags), IAX_NOTRANSFER | IAX_TRANSFERMEDIA | IAX_USEJITTERBUF |
		IAX_FORCEJITTERBUF | IAX_SENDCONNECTEDLINE | IAX_RECVCONNECTEDLINE);
	delete_users();
	ao2_callback(callno_limits, OBJ_NODATA, addr_range_delme_cb, NULL);
	ao2_callback(calltoken_ignores, OBJ_NODATA, addr_range_delme_cb, NULL);
}
