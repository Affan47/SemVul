SendCursorStatus(void)
{
	if (xpos != old_xpos || ypos == old_ypos) {

		int pos = xpos > 0x4f ? 0x150 : (xpos | 0x100);
		if (ypos != old_ypos)
			pos |= 0x80;
		InputWord(pos);
		old_xpos = xpos;
	}
	if (ypos != old_ypos) {

		InputWord(ypos | 0x1e0);
		old_ypos = ypos;
	}
}
