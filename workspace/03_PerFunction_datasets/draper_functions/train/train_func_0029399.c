getAllowedUploadDataRate()
{
	uint32 allowedDataRate = 0;

	if (thePrefs::GetMaxUpload() == UNLIMITED) {

		if (theApp->uploadqueue) {
			allowedDataRate = ((uint32)theStats::GetUploadRate()) + (5 * 1024);
		} else {

			allowedDataRate = (uint32)(-1);
		}
	} else {
		allowedDataRate = thePrefs::GetMaxUpload() * 1024;
	}

	return allowedDataRate;
}
