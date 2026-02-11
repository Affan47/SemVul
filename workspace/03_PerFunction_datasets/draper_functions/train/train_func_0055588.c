action_seek (Unit *unit, dpacket packet)
{
	Key *k = lookup_key (unit, GET_PCK_ARG1 (packet));
	long pos = (uae_s32)GET_PCK_ARG2 (packet);
	long mode = (uae_s32)GET_PCK_ARG3 (packet);
	uae_s64 res;
	uae_s64 cur;
	int whence = SEEK_CUR;
	uae_s64 temppos, filesize;

	if (k == 0) {
		PUT_PCK_RES1 (packet, -1);
		PUT_PCK_RES2 (packet, ERROR_INVALID_LOCK);
		return;
	}

	if (mode > 0)
		whence = SEEK_END;
	if (mode < 0)
		whence = SEEK_SET;

	cur = k->file_pos;
	TRACE((_T("ACTION_SEEK(%s,%d,%d)=%d\n"), k->aino->nname, pos, mode, cur));
	gui_flicker_led (UNIT_LED(unit), unit->unit, 1);

	filesize = fs_fsize64 (k->fd);
	if (whence == SEEK_CUR)
		temppos = cur + pos;
	if (whence == SEEK_SET)
		temppos = pos;
	if (whence == SEEK_END)
		temppos = filesize + pos;
	if (filesize < temppos) {
		PUT_PCK_RES1 (packet, -1);
		PUT_PCK_RES2 (packet, ERROR_SEEK_ERROR);
		return;
	}

	res = fs_lseek64 (k->fd, pos, whence);
	if (-1 == res || cur > MAXFILESIZE32) {
		PUT_PCK_RES1 (packet, -1);
		PUT_PCK_RES2 (packet, ERROR_SEEK_ERROR);
		fs_lseek64 (k->fd, cur, SEEK_SET);
	} else {
		PUT_PCK_RES1 (packet, cur);
		k->file_pos = fs_lseek64 (k->fd, 0, SEEK_CUR);
	}
}
