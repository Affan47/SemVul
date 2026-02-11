check_log_max_size( char *maxdiskspace_str,
                    char *mlogsize_str,
                    int maxdiskspace,
                    int mlogsize,
                    char * returntext,
                    int logtype)
{
    slapdFrontendConfig_t *slapdFrontendConfig = getFrontendConfig();
    int rc = LDAP_SUCCESS;
    int     current_mlogsize = -1;
    int     current_maxdiskspace = -1;
    PRInt64 mlogsizeB;
    PRInt64 maxdiskspaceB;

    switch (logtype)
    {
        case SLAPD_ACCESS_LOG:
            current_mlogsize = slapdFrontendConfig->accesslog_maxlogsize;
            current_maxdiskspace = slapdFrontendConfig->accesslog_maxdiskspace;
            break;
        case SLAPD_ERROR_LOG:
            current_mlogsize = slapdFrontendConfig->errorlog_maxlogsize;
            current_maxdiskspace = slapdFrontendConfig->errorlog_maxdiskspace;
            break;
        case SLAPD_AUDIT_LOG:
            current_mlogsize = slapdFrontendConfig->auditlog_maxlogsize;
            current_maxdiskspace = slapdFrontendConfig->auditlog_maxdiskspace;
            break;
        default:
            current_mlogsize = -1;
            current_maxdiskspace = -1;
    }

    if ( maxdiskspace == -1 ) {
        maxdiskspace = current_maxdiskspace;
    }

    if ( maxdiskspace == -1 ) {
        maxdiskspaceB = -1;
    } else {
        maxdiskspaceB = (PRInt64)maxdiskspace * LOG_MB_IN_BYTES;
    }

    if ( mlogsize == -1 ) {
        mlogsize = current_mlogsize;
    }

    if ( mlogsize == -1 ) {
        mlogsizeB = -1;
    } else {
        mlogsizeB = (PRInt64)mlogsize * LOG_MB_IN_BYTES;
    }


    if (( maxdiskspace >= 0 ) && ( maxdiskspace < mlogsize ))
    {

        PR_snprintf ( returntext, SLAPI_DSE_RETURNTEXT_SIZE,
          "%s: maxdiskspace \"%d (MB)\" is less than max log size \"%d (MB)\"",
          maxdiskspace_str, maxdiskspace, mlogsize );
        rc = LDAP_OPERATIONS_ERROR;
    }
    switch (logtype)
    {
        case SLAPD_ACCESS_LOG:
            loginfo.log_access_maxlogsize = mlogsizeB;
            loginfo.log_access_maxdiskspace = maxdiskspaceB;
            break;
        case SLAPD_ERROR_LOG:
            loginfo.log_error_maxlogsize = mlogsizeB;
            loginfo.log_error_maxdiskspace = maxdiskspaceB;
            break;
        case SLAPD_AUDIT_LOG:
            loginfo.log_audit_maxlogsize = mlogsizeB;
            loginfo.log_audit_maxdiskspace = maxdiskspaceB;
            break;
        default:
            break;
    }

    return rc;
}
