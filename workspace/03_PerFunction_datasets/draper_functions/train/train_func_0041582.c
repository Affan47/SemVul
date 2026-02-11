xjMouseCopyCut()
{
	register Mark	*mp = curmark;

	if (MouseParams(MPROTO_JOVETOOL)) {
		if (mp!=NULL
		&& (mp->m_line != curline || mp->m_char != curchar))
		{
			switch(but_state & (JT_CSMASK | JT_PASTEMASK)) {
			case JT_CONTROL:
				CopyRegion();
				last_mouse_act = LMA_COPY;
				break;
			case JT_CONTROL | JT_SHIFT:
				last_mouse_act = ObeyProc(DelReg)? LMA_CUT : LMA_NONE;
				break;
			case JT_PASTE:
				CopyRegion();
				SetWind(oldwind);
				ToMark(oldpos);
				ObeyProc(Yank);
				DelMark(oldpos);
				oldpos = NULL;
				last_mouse_act = LMA_COPY | LMA_PASTE;
				break;
			case JT_CUT:
				ObeyProc(DelReg);
				SetWind(oldwind);
				ToMark(oldpos);
				ObeyProc(Yank);
				DelMark(oldpos);
				oldpos = NULL;
				last_mouse_act = LMA_CUT | LMA_PASTE;
				break;

			}
		} else if (but_state & JT_PASTEMASK) {
			SetWind(oldwind);
			ToMark(oldpos);
			DelMark(oldpos);
			oldpos = NULL;
		}
	}
}
