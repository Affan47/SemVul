__acl_init_targetattrfilter( Targetattrfilter *attrfilter,
										char *str ) {

	char *tmp_ptr, *s, *filter_ptr;
	Slapi_Filter *f	= NULL;

	s = str;


    if ( (tmp_ptr = strstr( str, ":")) == NULL ) {

  		slapi_log_error(SLAPI_LOG_ACL, plugin_name,
                                "Bad targetattrfilter %s:%s\n",
                                str,"Expecting \":\"");

		return(ACL_SYNTAX_ERR);
	}
	*tmp_ptr = '\0';
	LDAP_UTF8INC(tmp_ptr);

    __acl_strip_trailing_space(s);


	if ( *s == '\0' ) {
		slapi_log_error(SLAPI_LOG_ACL, plugin_name,
                                "No attribute name in targattrfilters\n");
		return(ACL_SYNTAX_ERR);
	}

    attrfilter->attr_str = slapi_ch_strdup (s);


	filter_ptr = tmp_ptr;
	__acl_strip_leading_space(&filter_ptr);
	__acl_strip_trailing_space(filter_ptr);


	tmp_ptr = __acl_trim_filterstr(filter_ptr);

	if ((f = slapi_str2filter(tmp_ptr)) == NULL) {
  		slapi_log_error(SLAPI_LOG_ACL, plugin_name,
                                "Bad targetattr filter for attribute %s:%s\n",
                                attrfilter->attr_str,tmp_ptr);
        slapi_ch_free( (void **) &attrfilter->attr_str);
		slapi_ch_free( (void **) &tmp_ptr);
		return(ACL_SYNTAX_ERR);
	}


	if (acl_verify_exactly_one_attribute( attrfilter->attr_str, f) !=
				SLAPI_FILTER_SCAN_NOMORE) {
  		slapi_log_error(SLAPI_LOG_ACL, plugin_name,
              "Exactly one attribute type per filter allowed in targattrfilters (%s)\n",
				attrfilter->attr_str);
        slapi_ch_free( (void **) &attrfilter->attr_str);
		slapi_ch_free( (void **) &tmp_ptr);
		slapi_filter_free( f, 1 );
		return(ACL_SYNTAX_ERR);
	}


	slapi_ch_free( (void **) &tmp_ptr);
    attrfilter->filterStr = slapi_ch_strdup (filter_ptr);
	attrfilter->filter = f;

	return(LDAP_SUCCESS);
}
