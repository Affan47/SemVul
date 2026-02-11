_rsvg_node_text_length_tspan (RsvgNodeText * self,
                              RsvgDrawingCtx * ctx, gdouble * length,
                              gboolean * lastwasspace, gboolean usetextonly)
{
    if (self->x.factor != 'n' || self->y.factor != 'n')
        return TRUE;

    if (PANGO_GRAVITY_IS_VERTICAL (rsvg_current_state (ctx)->text_gravity))
        *length += _rsvg_css_normalize_length (&self->dy, ctx, 'v');
    else
        *length += _rsvg_css_normalize_length (&self->dx, ctx, 'h');

    return _rsvg_node_text_length_children (&self->super, ctx, length,
                                             lastwasspace, usetextonly);
}
