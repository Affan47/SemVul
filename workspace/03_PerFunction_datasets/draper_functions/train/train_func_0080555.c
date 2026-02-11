WI_drawAnimatedBack(void)
{
    int			i;
    anim_t*		a;

    if (gamemode == commercial)
	return;

    if (wbs->epsd > 2)
	return;

    for (i=0 ; i<NUMANIMS[wbs->epsd] ; i++)
    {
	a = &anims[wbs->epsd][i];

	if (a->ctr >= 0)
	    V_DrawPatch(a->loc.x, a->loc.y, a->p[a->ctr]);
    }

}
