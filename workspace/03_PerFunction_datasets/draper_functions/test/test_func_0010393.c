shepherd_error_exit()
{
    int  old_euid = SGE_SUPERUSER_UID;


   if (getuid() == SGE_SUPERUSER_UID) {
      old_euid = geteuid();
      seteuid(SGE_SUPERUSER_UID);
   }


	if (shepherd_error_fp) {
		FCLOSE_IGNORE_ERROR(shepherd_error_fp);
      shepherd_error_fp = NULL;
	}
	if (shepherd_exit_status_fp) {
		FCLOSE_IGNORE_ERROR(shepherd_exit_status_fp);
      shepherd_exit_status_fp = NULL;
	}


   if (old_euid != SGE_SUPERUSER_UID) {
      seteuid(old_euid);
   }
}
