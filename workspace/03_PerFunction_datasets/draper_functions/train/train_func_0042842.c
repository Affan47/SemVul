DS_LASSSFEval(NSErr_t *errp, char *attr_name, CmpOp_t comparator,
                char *attr_pattern, int *cachable, void **LAS_cookie,
                PList_t subject, PList_t resource, PList_t auth_info,
                PList_t global_auth)
{
	char            *attr;
	char            *ptr;
	int             len;
	int             rc;
	lasInfo         lasinfo;
	int		aclssf;

	if ( 0 !=  (rc = __acllas_setup (errp, attr_name, comparator, 1,
					attr_pattern,cachable,LAS_cookie,
					subject, resource, auth_info,global_auth,
					DS_LAS_SSF, "DS_LASSSFEval",
					&lasinfo )) ) {
		return LAS_EVAL_FAIL;
	}

	attr = attr_pattern;


	while(ldap_utf8isspace(attr)) LDAP_UTF8INC(attr);
	len = strlen(attr);
	ptr = attr+len-1;
	while(ptr >= attr && ldap_utf8isspace(ptr)) {
		*ptr = '\0';
		LDAP_UTF8DEC(ptr);
	}


	aclssf = (int) strtol(attr, &ptr, 10);
	if (*ptr != '\0') {
		rc = LAS_EVAL_FAIL;
		slapi_log_error( SLAPI_LOG_ACL, plugin_name,
			"Error parsing numeric SSF from bind rule.\n");
		slapi_log_error( SLAPI_LOG_ACL, plugin_name,
			"Returning UNDEFINED for ssf evaluation.\n");
	}


	if ((aclssf < 0) || (((aclssf == INT_MAX) || (aclssf == INT_MIN)) && (errno == ERANGE))){
		rc = LAS_EVAL_FAIL;
		slapi_log_error( SLAPI_LOG_ACL, plugin_name,
			"SSF \"%s\" is invalid. Value must range from 0 to %d",
			attr, INT_MAX);
		slapi_log_error( SLAPI_LOG_ACL, plugin_name,
			"Returning UNDEFINED for ssf evaluation.\n");
	}

	slapi_log_error( SLAPI_LOG_ACL, plugin_name,
		"DS_LASSSFEval: aclssf:%d, ssf:%d\n",
		aclssf, lasinfo.ssf);

	switch ((int)comparator) {
		case CMP_OP_EQ:
			if (lasinfo.ssf == aclssf) {
				rc = LAS_EVAL_TRUE;
			} else {
				rc = LAS_EVAL_FALSE;
			}
			break;
		case CMP_OP_NE:
			if (lasinfo.ssf != aclssf) {
				rc = LAS_EVAL_TRUE;
			} else {
				rc = LAS_EVAL_FALSE;
			}
			break;
		case CMP_OP_GT:
			if (lasinfo.ssf > aclssf) {
				rc = LAS_EVAL_TRUE;
			} else {
				rc = LAS_EVAL_FALSE;
			}
			break;
		case CMP_OP_LT:
			if (lasinfo.ssf < aclssf) {
				rc = LAS_EVAL_TRUE;
			} else {
				rc = LAS_EVAL_FALSE;
			}
			break;
		case CMP_OP_GE:
			if (lasinfo.ssf >= aclssf) {
				rc = LAS_EVAL_TRUE;
			} else {
				rc = LAS_EVAL_FALSE;
			}
			break;
		case CMP_OP_LE:
			if (lasinfo.ssf <= aclssf) {
				rc = LAS_EVAL_TRUE;
			} else {
				rc = LAS_EVAL_FALSE;
			}
			break;
		default:


			rc = LAS_EVAL_FAIL;
			slapi_log_error( SLAPI_LOG_ACL, plugin_name,
				"Invalid comparator \"%d\" evaluating SSF.\n",
				(int)comparator);
			slapi_log_error( SLAPI_LOG_ACL, plugin_name,
				"Returning UNDEFINED for ssf evaluation.\n");
	}

	return rc;
}
