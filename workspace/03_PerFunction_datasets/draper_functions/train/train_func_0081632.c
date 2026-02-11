do_pamcheck(const char* user, const char* passwd, const char* remoteaddr)
{


    bool retval = false;
    uid_t ouid = geteuid();
    (void) seteuid(0);

    int pamret = PAM_SUCCESS;;
    pam_handle_t *pamh;
    struct pam_conv conv = {pamconv, (void*)passwd};

    pamret = pam_start(FAX_SERVICE, user, &conv, &pamh);
    if (pamret != PAM_SUCCESS)
    {
	logNotice("pam_start failed in pamCheck with 0x%X: %s", pamret, pam_strerror(pamh, pamret));
	return false;
    }
    pamret = pam_set_item(pamh, PAM_RHOST, remoteaddr);
    if (pamret == PAM_SUCCESS)
    {
    	pamret = do_pamauth(pamh);
	if (pamret == PAM_SUCCESS)
	    retval = true;
	else
	    logNotice("pam_authenticate failed in pamCheck with 0x%X: %s", pamret, pam_strerror(pamh, pamret));
    } else
	logNotice("pam_set_item (PAM_RHOST) failed in pamCheck with 0x%X: %s", pamret, pam_strerror(pamh, pamret));


    pamret = pam_end(pamh, pamret);

    if (pamret != PAM_SUCCESS)
	logNotice("pam_end failed with 0x%X: %s", pamret, pam_strerror(pamh, pamret));

    (void) seteuid(ouid);


    HylaFAXServer::setupLogging();

    return retval;
}
