border_get_titlebar_draw_descr(
	FvwmWindow *fw, titlebar_descr *td, title_draw_descr *tdd,
	Pixmap dest_pix)
{
	memset(tdd, 0, sizeof(*tdd));

	if (td->tbstate.is_title_pressed)
	{
		tdd->rgc = td->cd->shadow_gc;
		tdd->sgc = td->cd->relief_gc;
	}
	else
	{
		tdd->rgc = td->cd->relief_gc;
		tdd->sgc = td->cd->shadow_gc;
	}
	NewFontAndColor(fw->title_font, td->cd->fore_color, td->cd->back_color);
	tdd->tstyle = &TB_STATE(
		GetDecor(fw, titlebar))[td->tbstate.tstate].style;
	tdd->df = &TB_STATE(GetDecor(fw, titlebar))[td->tbstate.tstate];


	tdd->fstr.str = fw->visible_name;
	tdd->fstr.win = dest_pix;
	if (td->td_is_rotated)
	{
		tdd->fstr.flags.text_rotation = ROTATION_0;
	}
	else
	{
		tdd->fstr.flags.text_rotation = fw->title_text_rotation;
	}
	if (td->has_vt)
	{
		tdd->fstr.y = td->offset;
		tdd->fstr.x = fw->title_text_offset + 1;
	}
	else
	{
		tdd->fstr.x = td->offset;
		tdd->fstr.y = fw->title_text_offset + 1;
	}
	if (td->cd->cs >= 0)
	{
		tdd->fstr.colorset = &Colorset[td->cd->cs];
		tdd->fstr.flags.has_colorset = 1;
	}
	tdd->fstr.gc = Scr.TitleGC;

	return;
}
