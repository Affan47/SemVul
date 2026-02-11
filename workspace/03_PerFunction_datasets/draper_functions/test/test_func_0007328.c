log_file_preference(uconf_log_file_preference_ty dflt)
{
    uconf_ty *ucp = uconf_get();
    if (ucp->mask & uconf_log_file_preference_mask)
	return ucp->log_file_preference;
    return dflt;
}
