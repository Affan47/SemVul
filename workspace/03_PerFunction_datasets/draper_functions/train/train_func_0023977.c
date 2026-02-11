eapChanged(int sel)
{
	QString prev_val = phase2Select->currentText();
	while (phase2Select->count())
		phase2Select->removeItem(0);

	QStringList inner;
	inner << "PEAP" << "TTLS" << "FAST";
	if (!inner.contains(eapSelect->itemText(sel)))
		return;

	phase2Select->addItem("[ any ]");


	if (eapSelect->currentText().compare("TTLS") == 0) {
		phase2Select->addItem("PAP");
		phase2Select->addItem("CHAP");
		phase2Select->addItem("MSCHAP");
		phase2Select->addItem("MSCHAPv2");
	} else if (eapSelect->currentText().compare("FAST") == 0)
		phase2Select->addItem("GTC(auth) + MSCHAPv2(prov)");


	int i;
	QStringList allowed;
	allowed << "MSCHAPV2" << "MD5" << "GTC" << "TLS" << "OTP" << "SIM"
		<< "AKA";
	for (i = 0; i < eapSelect->count(); i++) {
		if (allowed.contains(eapSelect->itemText(i))) {
			phase2Select->addItem("EAP-" + eapSelect->itemText(i));
		}
	}

	for (i = 0; i < phase2Select->count(); i++) {
		if (phase2Select->itemText(i).compare(prev_val) == 0) {
			phase2Select->setCurrentIndex(i);
			break;
		}
	}
}
