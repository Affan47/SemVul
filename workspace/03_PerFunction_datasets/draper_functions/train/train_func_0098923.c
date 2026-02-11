save_image(void)
{
	int i;

	if (!need_saving)
		return;
	for (i = 0; i < maxROWS; i++) {
		(void) memmove(ea_save[appres.save_lines+i],
		            (ea_buf + (i*COLS)),
		            COLS*sizeof(struct ea));
	}
	need_saving = False;
}
