Validate()
{
	wxTextCtrl* pRetries = XRCCTRL(*this, "ID_RETRIES", wxTextCtrl);

	long retries;
	if (!pRetries->GetValue().ToLong(&retries) || retries < 0 || retries > 99)
		return DisplayError(pRetries, _("Number of retries has to be between 0 and 99."));

	wxTextCtrl* pDelay = XRCCTRL(*this, "ID_RETRYDELAY", wxTextCtrl);

	long delay;
	if (!pDelay->GetValue().ToLong(&delay) || delay < 0 || delay > 999)
		return DisplayError(pDelay, _("Delay between failed connection attempts has to be between 1 and 999 seconds."));

	long timeout;
	wxTextCtrl *pTimeout = XRCCTRL(*this, "ID_TIMEOUT", wxTextCtrl);
	if (!pTimeout->GetValue().ToLong(&timeout) || ((timeout < 5 || timeout > 9999) && timeout != 0))
		return DisplayError(pTimeout, _("Please enter a timeout between 5 and 9999 seconds or 0 to disable timeouts."));

	return true;
}
