setAlert(const PsiIcon *icon)
{
	bool reset = false;

	if ( !d->alerting ) {
		d->alerting = true;
		reset = true;
	}
	else {
		if ( d->lastIcon != icon )
			reset = true;
	}

	if ( reset )
		setIcon(icon, true);
}
