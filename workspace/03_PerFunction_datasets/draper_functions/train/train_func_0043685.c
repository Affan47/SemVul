SelectDevice(int row)
{
	if (row >= 0)
		removeDeviceButton->setEnabled(true);
	else
		removeDeviceButton->setEnabled(false);
}
