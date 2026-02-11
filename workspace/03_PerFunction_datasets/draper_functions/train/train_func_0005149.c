init(gfxengine_t *e)
{
	link(e);
	xs = engine->xs;
	ys = engine->ys;
	if(_offscreen && surface)
	{
		SDL_FreeSurface(surface);
		surface = NULL;
	}
	_offscreen = 0;
	surface = engine->surface();
}
