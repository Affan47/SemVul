SIO_StateSave(void)
{
	int i;

	for (i = 0; i < 8; i++) {
		StateSav_SaveINT((int *) &SIO_drive_status[i], 1);
		StateSav_SaveFNAME(SIO_filename[i]);
	}
}
