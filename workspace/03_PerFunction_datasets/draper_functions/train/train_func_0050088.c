gmlc_mysql_query_get_current_charset(GmlcMysqlQuery * pGmlcMysqlQry) {
	gchar * pcCharset = NULL;

	g_return_val_if_fail(pGmlcMysqlQry != NULL, NULL);

	if (pGmlcMysqlQry->pMysqlLink == NULL) {
		gmlc_mysql_query_connect(pGmlcMysqlQry);
	}

	if (pGmlcMysqlQry->pMysqlLink == NULL) {
		return NULL;
	}

	if (pGmlcMysqlQry->lVersion >= 40100) {
		pcCharset = gmlc_tools_query_get_one_result(pGmlcMysqlQry->pMysqlLink, "ISO-8859-1", "SHOW VARIABLES LIKE 'character_set_results'", 1);

		if (pcCharset != NULL) {
			g_free(pGmlcMysqlQry->pcSrvCharset);
			pGmlcMysqlQry->pcSrvCharset = pcCharset;
		}
	} else {
		pcCharset = gmlc_tools_query_get_one_result(pGmlcMysqlQry->pMysqlLink, "ISO-8859-1", "SHOW VARIABLES LIKE 'character_set'", 1);

		if (pcCharset != NULL) {
			g_free(pGmlcMysqlQry->pcSrvCharset);
			pGmlcMysqlQry->pcSrvCharset = pcCharset;
		}
	}

	return pGmlcMysqlQry->pcSrvCharset;
}
