authChanged(int sel)
{
	encrSelect->setEnabled(sel != AUTH_NONE_OPEN && sel != AUTH_NONE_WEP &&
			       sel != AUTH_NONE_WEP_SHARED);
	pskEdit->setEnabled(sel == AUTH_WPA_PSK || sel == AUTH_WPA2_PSK);
	bool eap = sel == AUTH_IEEE8021X || sel == AUTH_WPA_EAP ||
		sel == AUTH_WPA2_EAP;
	eapSelect->setEnabled(eap);
	identityEdit->setEnabled(eap);
	passwordEdit->setEnabled(eap);
	cacertEdit->setEnabled(eap);
	phase2Select->setEnabled(eap);
	if (eap)
		eapChanged(eapSelect->currentIndex());

	while (encrSelect->count())
		encrSelect->removeItem(0);

	if (sel == AUTH_NONE_OPEN || sel == AUTH_NONE_WEP ||
	    sel == AUTH_NONE_WEP_SHARED || sel == AUTH_IEEE8021X) {
		encrSelect->addItem("None");
		encrSelect->addItem("WEP");
		encrSelect->setCurrentIndex(sel == AUTH_NONE_OPEN ? 0 : 1);
	} else {
		encrSelect->addItem("TKIP");
		encrSelect->addItem("CCMP");
		encrSelect->setCurrentIndex((sel == AUTH_WPA2_PSK ||
					     sel == AUTH_WPA2_EAP) ? 1 : 0);
	}

	wepEnabled(sel == AUTH_NONE_WEP || sel == AUTH_NONE_WEP_SHARED);
}
