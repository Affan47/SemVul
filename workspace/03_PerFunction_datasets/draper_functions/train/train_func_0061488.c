playlist_progress(void *instance, int phase, int param_int, void *param_ptr)
{
	char mbs[MAX_PATH+1];
	progress_data_t* pd = (progress_data_t*)instance;
	FILE *fp = pd->fp;

	switch (phase) {

	case EASYH10P_ENUMTARGETS_START:
		fprintf(fp, "Enumerating playlists:\n");
		break;
	case EASYH10P_ENUMTARGETS_FILE:
		ucs2tombs(mbs, MAX_PATH, (const ucs2_char_t*)param_ptr, ucs2len((const ucs2_char_t*)param_ptr)+1);
		fprintf(fp, "  %d: %-70.70s\r", param_int, mbs);
		break;
	case EASYH10P_ENUMTARGETS_END:
		fprintf(fp, "  %d playlists found.%-58.58s\n", param_int, "");
		fprintf(fp, "\n");
		break;

	case EASYH10P_PLAYLIST_ENUMMUSIC_START:
		fprintf(fp, "Enumerating music files:\n");
		break;
	case EASYH10P_PLAYLIST_ENUMMUSIC_FILE:
		ucs2tombs(mbs, MAX_PATH, (const ucs2_char_t*)param_ptr, ucs2len((const ucs2_char_t*)param_ptr)+1);
		fprintf(fp, "  %d: %-70.70s\r", param_int, mbs);
		break;
	case EASYH10P_PLAYLIST_ENUMMUSIC_END:
		fprintf(fp, "  %d files found.%-60.60s\n", param_int, "");
		fprintf(fp, "\n");
		break;


	case EASYH10P_PLAYLIST_START:
		fprintf(fp, "Converting %d playlists:\n", param_int);
		pd->num = param_int;
		break;
	case EASYH10P_PLAYLIST:
		ucs2tombs(mbs, MAX_PATH, (const ucs2_char_t*)param_ptr, ucs2len((const ucs2_char_t*)param_ptr)+1);
		fprintf(fp, "  %d: %-70.70s\r", param_int, mbs);
		break;
	case EASYH10P_PLAYLIST_END:
		fprintf(fp, "  %d playlists successfully converted.%-40.40s\n", param_int, "");
		fprintf(fp, "\n");
		break;
	}

	pd->prev_phase = phase;
	fflush(fp);
	return 0;
}
