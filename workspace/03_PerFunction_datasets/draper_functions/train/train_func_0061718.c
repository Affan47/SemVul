evg_radial_gradient_brush()
{
	s32 i;
	EVG_RadialGradient *tmp;
	GF_SAFEALLOC(tmp, EVG_RadialGradient);
	if (!tmp) return 0L;

	tmp->fill_run = rg_fill_run;
	tmp->type = GF_STENCIL_RADIAL_GRADIENT;
	for(i=0; i<EVGGRADIENTSLOTS; i++) tmp->pos[i]=-1;

	tmp->center.x = tmp->center.y = FIX_ONE/2;
	tmp->focus = tmp->center;
	tmp->radius = tmp->center;
	tmp->alpha = 0xFF;
	return (EVGStencil *) tmp;
}
