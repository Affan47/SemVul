cd_setsongtime(memptr device, uint32 dummy, uint32 start_msf, uint32 end_msf)
{
	DUNUSED(dummy);
	int drive, errorcode;
	struct cdrom_msf audio_bloc;

	drive = OpenDrive(device);
	if (drive<0) {
		return EINVFN;
	}

	audio_bloc.cdmsf_min0 = (start_msf>>16) & 0xff;
	audio_bloc.cdmsf_sec0 = (start_msf>>8) & 0xff;
	audio_bloc.cdmsf_frame0 = (start_msf>>0) & 0xff;
	D(bug(NFCD_NAME " start: %02d:%02d:%02d", (start_msf>>16) & 0xff, (start_msf>>8) & 0xff, start_msf & 0xff));

	audio_bloc.cdmsf_min1 = (end_msf>>16) & 0xff;
	audio_bloc.cdmsf_sec1 = (end_msf>>8) & 0xff;
	audio_bloc.cdmsf_frame1 = (end_msf>>0) & 0xff;
	D(bug(NFCD_NAME " end:   %02d:%02d:%02d", (end_msf>>16) & 0xff, (end_msf>>8) & 0xff, end_msf & 0xff));

	errorcode=ioctl(drive_handles[drive], CDROMPLAYMSF, &audio_bloc);
	CloseDrive(drive);
	return errorcode;
}
