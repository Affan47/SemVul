rsvg_node_svg_set_atts (RsvgNode * self, RsvgHandle * ctx, RsvgPropertyBag * atts)
{
    const char *value;
    RsvgNodeSvg *svg = (RsvgNodeSvg *) self;

    if (rsvg_property_bag_size (atts)) {
        if ((value = rsvg_property_bag_lookup (atts, "viewBox")))
            svg->vbox = rsvg_css_parse_vbox (value);

        if ((value = rsvg_property_bag_lookup (atts, "preserveAspectRatio")))
            svg->preserve_aspect_ratio = rsvg_css_parse_aspect_ratio (value);
        if ((value = rsvg_property_bag_lookup (atts, "width")))
            svg->w = _rsvg_css_parse_length (value);
        if ((value = rsvg_property_bag_lookup (atts, "height")))
            svg->h = _rsvg_css_parse_length (value);


        if (self->parent && (value = rsvg_property_bag_lookup (atts, "x")))
            svg->x = _rsvg_css_parse_length (value);
        if (self->parent && (value = rsvg_property_bag_lookup (atts, "y")))
            svg->y = _rsvg_css_parse_length (value);
        if ((value = rsvg_property_bag_lookup (atts, "id"))) {
            rsvg_defs_register_name (ctx->priv->defs, value, &svg->super);
        }


        svg->atts = rsvg_property_bag_dup(atts);
    }
}
