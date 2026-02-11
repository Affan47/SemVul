dopam(pam_handle_t **pamh)
{
int	retval;

	DPRINTF("pam_service=%s, pam_username=%s",
		pam_service ? pam_service : "<null>",
		pam_username ? pam_username : "<null>");

	retval=pam_start(pam_service, pam_username, &conv, pamh);
	if (retval != PAM_SUCCESS)
	{
		DPRINTF("pam_start failed, result %d [Hint: bad PAM configuration?]", retval);
	}

#if 0
	if (retval == PAM_SUCCESS)
	{
		retval=pam_set_item(*pamh, PAM_AUTHTOK, pam_password);
		if (retval != PAM_SUCCESS)
		{
			DPRINTF("pam_set_item failed, result %d", retval);
		}
	}
#endif

	if (retval == PAM_SUCCESS)
	{
		retval=pam_authenticate(*pamh, 0);
		if (retval != PAM_SUCCESS)
		{
			DPRINTF("pam_authenticate failed, result %d", retval);
		}
	}

#if 0

#if	HAVE_PAM_SETCRED
	if (retval == PAM_SUCCESS)
	{
		retval=pam_setcred(*pamh, PAM_ESTABLISH_CRED);
		if (retval != PAM_SUCCESS)
		{
			DPRINTF("pam_setcred failed, result %d", retval);
		}
	}
#endif
#endif

	if (retval == PAM_SUCCESS)
	{
		retval=pam_acct_mgmt(*pamh, 0);
		if (retval != PAM_SUCCESS)
		{
			DPRINTF("pam_acct_mgmt failed, result %d", retval);
		}
	}
	if (retval == PAM_SUCCESS)
	{
		DPRINTF("dopam successful");
	}
	return (retval);
}
