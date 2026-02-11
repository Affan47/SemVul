bios_10_0axx(struct regs *regs)
{
	unsigned short rows;
	unsigned short cols;
	unsigned short x;
	unsigned short y;
	unsigned short i;

#ifdef DEBUG_INT10
        dprintf("VGA Function 0a: Print character only at cursor.\n");
#endif
	rows = var_get(vid_rows) + 1;
	cols = var_get(vid_columns);

	x = var_get(curspos[BH].x);
	y = var_get(curspos[BH].y);

	assert( x < cols);
	assert( y < rows);

	for (i = 0; i < CX; i++) {
		if (cols <= x + i) {
			break;
		}
		write_char(BH, x + i, y, AL, BL, 0);
	}
}
