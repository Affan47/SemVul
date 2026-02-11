gfxw_new_dyn_view(gfx_state_t *state, point_t pos, int z, int view, int loop, int cel, int palette, int priority, int control,
		  gfx_alignment_t halign, gfx_alignment_t valign, int sequence)
{
	gfxw_dyn_view_t *widget;
	int width, height;
	int xalignmod, yalignmod;
	point_t offset;

	if (!state) {
		GFXERROR("Attempt to create view widget with NULL state!\n");
		return NULL;
	}

	if (gfxop_get_cel_parameters(state, view, loop, cel, &width, &height, &offset)) {
		GFXERROR("Attempt to retreive cel parameters for (%d/%d/%d) failed (Maybe the values weren't checked beforehand?)\n",
			 view, cel, loop);
		return NULL;
	}

	widget = (gfxw_dyn_view_t *) _gfxw_new_widget(sizeof(gfxw_dyn_view_t), GFXW_DYN_VIEW);

	widget->pos = pos;
	widget->color.mask =
		((priority < 0)? 0 : GFX_MASK_PRIORITY)
		| ((control < 0)? 0 : GFX_MASK_CONTROL);
	widget->widget_priority = priority;
	widget->color.priority = priority;
	widget->color.control = control;
	widget->color.alpha = 0;
	widget->color.visual.global_index = 0;
	widget->color.visual.r = 0;
	widget->color.visual.g = 0;
	widget->color.visual.b = 0;
	widget->view = view;
	widget->loop = loop;
	widget->cel = cel;
	widget->sequence = sequence;
	widget->force_precedence = 0;
	widget->palette = palette;

	if (halign == ALIGN_CENTER)
		xalignmod = width >> 1;
	else if (halign == ALIGN_RIGHT)
		xalignmod = width;
	else
		xalignmod = 0;

	if (valign == ALIGN_CENTER)
		yalignmod = height >> 1;
	else if (valign == ALIGN_BOTTOM)
		yalignmod = height;
	else
		yalignmod = 0;

	widget->z = z;

	widget->draw_bounds = gfx_rect(widget->pos.x - xalignmod,
				       widget->pos.y - yalignmod - z, width, height);
	widget->bounds = gfx_rect(widget->pos.x - offset.x - xalignmod,
				  widget->pos.y - offset.y - yalignmod - z, width, height);

	widget->flags |= GFXW_FLAG_VISIBLE;

	_gfxw_set_ops_DYNVIEW(GFXW(widget));

	widget->signalp = NULL;
	widget->signal = 0;

	return widget;
}
