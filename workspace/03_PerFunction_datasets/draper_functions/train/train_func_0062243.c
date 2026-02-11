action_set_comment (Unit * unit, dpacket packet)
{
	uaecptr lock = GET_PCK_ARG2 (packet) << 2;
	uaecptr name = GET_PCK_ARG3 (packet) << 2;
	uaecptr comment = GET_PCK_ARG4 (packet) << 2;
	TCHAR *commented = NULL;
	a_inode *a;
	int err;

	if (unit->ui.readonly || unit->ui.locked) {
		PUT_PCK_RES1 (packet, DOS_FALSE);
		PUT_PCK_RES2 (packet, ERROR_DISK_WRITE_PROTECTED);
		return;
	}

	if (fsdb_cando (unit)) {
		commented = bstr (unit, comment);
		if (_tcslen (commented) > 80) {
			PUT_PCK_RES1 (packet, DOS_FALSE);
			PUT_PCK_RES2 (packet, ERROR_COMMENT_TOO_BIG);
			return;
		}
		if (_tcslen (commented) > 0) {
			TCHAR *p = commented;
			commented = xmalloc (TCHAR, 81);
			_tcsncpy (commented, p, 80);
			commented[80] = 0;
		} else {
			commented = NULL;
		}
	}
	TRACE ((_T("ACTION_SET_COMMENT(0x%lx,\"%s\")\n"), lock, commented));

	a = find_aino (unit, lock, bstr (unit, name), &err);
	if (err != 0) {
		PUT_PCK_RES1 (packet, DOS_FALSE);
		PUT_PCK_RES2 (packet, err);

maybe_free_and_out:
		if (commented)
			xfree (commented);
		return;
	}
	PUT_PCK_RES1 (packet, DOS_TRUE);
	PUT_PCK_RES2 (packet, 0);
	if (a->comment == 0 && commented == 0)
		goto maybe_free_and_out;
	if (a->comment != 0 && commented != 0 && _tcscmp (a->comment, commented) == 0)
		goto maybe_free_and_out;
	if (a->comment)
		xfree (a->comment);
	a->comment = commented;
	fsdb_set_file_attrs (a);
	notify_check (unit, a);
	gui_flicker_led (UNIT_LED(unit), unit->unit, 2);
}
