_gda_xslt_bk_fun_getvalue (xmlChar * set, xmlChar * name, GdaXsltExCont * exec,
			  GdaXsltIntCont * pdata,int getXml)
{
	xmlXPathObjectPtr value;
	int res;
	xmlDocPtr sqlxmldoc;
	xmlNodePtr rootnode;
	xmlNodePtr copyrootnode;
#ifdef GDA_DEBUG_NO
	g_print ("running function:_gda_xslt_bk_fun_getvalue (getxml [%d])", getXml);
#endif
	char *strvalue;
	res = get_resultset_col_value (pdata, (const char *) set,
				       (const char *) name, &strvalue,
				       &(exec->error));
	if (res < 0) {
		xsltGenericError (xsltGenericErrorContext,
				  "_gda_xslt_bk_fun_getvalue: internal error on get_resultset_col_value\n");
		return NULL;
	}

	if( getXml) {
		sqlxmldoc = xmlParseDoc((const xmlChar *)strvalue);
		if (sqlxmldoc == NULL) {
			xsltGenericError (xsltGenericErrorContext,
					"_gda_xslt_bk_fun_getvalue: xmlParseDoc fauld\n");
			return NULL;
		}
		rootnode = xmlDocGetRootElement(sqlxmldoc);
		copyrootnode = xmlCopyNode(rootnode,1);
		if (copyrootnode == NULL) {
			xsltGenericError (xsltGenericErrorContext,
					"_gda_xslt_bk_fun_getvalue: get or copy of root node fauld\n");
			return NULL;
		}
		value = (xmlXPathObjectPtr) xmlXPathNewNodeSet (copyrootnode);
		xmlFreeDoc(sqlxmldoc );
	} else {
		value = (xmlXPathObjectPtr) xmlXPathNewCString ((const char *)
								strvalue);
	}

	if (value == NULL) {
		xsltGenericError (xsltGenericErrorContext,
				  "_gda_xslt_bk_fun_getvalue: internal error\n");
		return NULL;
	}
	return value;
}
