refresh_rect(SDL_Rect *r)
{
	window_t *w = windows;
	for(w = windows; w; w = w->next)
	{
		if(!w->visible())
			continue;

		SDL_Rect dr = *r;


		int Amin, Amax, Bmin, Bmax;


		Amin = dr.x;
		Amax = Amin + dr.w;
		Bmin = w->phys_rect.x;
		Bmax = Bmin + w->phys_rect.w;
		if(Bmin > Amin)
			Amin = Bmin;
		dr.x = Amin;
		if(Bmax < Amax)
			Amax = Bmax;
		dr.w = Amax - Amin > 0 ? Amax - Amin : 0;


		Amin = dr.y;
		Amax = Amin + dr.h;
		Bmin = w->phys_rect.y;
		Bmax = Bmin + w->phys_rect.h;
		if(Bmin > Amin)
			Amin = Bmin;
		dr.y = Amin;
		if(Bmax < Amax)
			Amax = Bmax;
		dr.h = Amax - Amin > 0 ? Amax - Amin : 0;

		if(dr.w && dr.h)
			w->phys_refresh(&dr);
	}
}
