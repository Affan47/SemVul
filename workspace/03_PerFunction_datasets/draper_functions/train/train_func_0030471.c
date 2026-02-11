nemo_file_can_set_owner (NemoFile *file)
{


	if (!nemo_file_can_get_owner (file)) {
		return FALSE;
	}


	return geteuid() == 0;
}
