draw(
	const CL_Surface_DrawParams1& params1,
	CL_GraphicContext *gc)
{
	if (gc == 0) gc = CL_Display::get_current_window()->get_gc();
	impl->target->draw(
		impl,
		params1,
		gc);
}
