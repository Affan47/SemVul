acllas_eval_one_target_filter( char * str, Slapi_Entry *e) {

	int rc = ACL_FALSE;
	Slapi_Filter *f = NULL;

	PR_ASSERT(str);

	if ((f = slapi_str2filter(str)) == NULL) {
		slapi_log_error(SLAPI_LOG_FATAL, plugin_name,
        	"Warning: Bad targetfilter(%s) in aci: does not match\n", str);
		return(ACL_DONT_KNOW);
	}

	if (slapi_vattr_filter_test(NULL, e, f, 0 )!= 0) {
			rc = ACL_FALSE;
	} else {
			rc = ACL_TRUE;
	}
	slapi_filter_free(f, 1);

	return(rc);

}
