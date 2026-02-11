stopWpsRun(bool success)
{
	if (wpsRunning)
		wpsStatusText->setText(success ? tr("Connected to the network") :
				       tr("Stopped"));
	else
		wpsStatusText->setText("");
	wpsPinEdit->setEnabled(false);
	wpsInstructions->setText("");
	wpsRunning = false;
	bssFromScan = "";
	wpsApPinEdit->setEnabled(false);
	wpsApPinButton->setEnabled(false);
}
