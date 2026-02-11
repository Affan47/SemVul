ccid_check_firmware(struct libusb_device_descriptor *desc)
{
	unsigned int i;

	for (i=0; i<COUNT_OF(Bogus_firmwares); i++)
	{
		if (desc->idVendor != Bogus_firmwares[i].vendor)
			continue;

		if (desc->idProduct != Bogus_firmwares[i].product)
			continue;


		if (desc->bcdDevice < Bogus_firmwares[i].firmware)
		{
			if (DriverOptions & DRIVER_OPTION_USE_BOGUS_FIRMWARE)
			{
				DEBUG_INFO3("Firmware (%X.%02X) is bogus! but you choosed to use it",
					desc->bcdDevice >> 8, desc->bcdDevice & 0xFF);
				return FALSE;
			}
			else
			{
				DEBUG_CRITICAL3("Firmware (%X.%02X) is bogus! Upgrade the reader firmware or get a new reader.",
					desc->bcdDevice >> 8, desc->bcdDevice & 0xFF);
				return TRUE;
			}
		}
	}


	return FALSE;
}
