g3_draw_line(vertex *p0,vertex *p1)
{
#ifdef FRED_OGL_COMMENT_OUT_FOR_NOW
	if(Fred_running && !Cmdline_nohtl)
	{
  		gr_aaline( p0, p1 );
		return 0;
	}
#endif

	ubyte codes_or;

	Assert( G3_count == 1 );

	if (p0->codes & p1->codes)
		return 0;

	codes_or = (unsigned char)(p0->codes | p1->codes);

	if (codes_or & CC_BEHIND)
		return must_clip_line(p0,p1,codes_or,0);

	if (!(p0->flags&PF_PROJECTED))
		g3_project_vertex(p0);

	if (p0->flags&PF_OVERFLOW)
		return must_clip_line(p0,p1,codes_or,0);


	if (!(p1->flags&PF_PROJECTED))
		g3_project_vertex(p1);

	if (p1->flags&PF_OVERFLOW)
		return must_clip_line(p0,p1,codes_or,0);

  	gr_aaline( p0, p1 );

	return 0;
}
