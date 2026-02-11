RrFontOpen(const RrInstance *inst, const gchar *name, gint size,
                   RrFontWeight weight, RrFontSlant slant)
{
    RrFont *out;
    PangoWeight pweight;
    PangoStyle pstyle;
    PangoAttrList *attrlist;

    out = g_slice_new(RrFont);
    out->inst = inst;
    out->ref = 1;
    out->font_desc = pango_font_description_new();
    out->layout = pango_layout_new(inst->pango);
    out->shortcut_underline = pango_attr_underline_new(PANGO_UNDERLINE_LOW);
    out->shortcut_underline->start_index = 0;
    out->shortcut_underline->end_index = 0;

    attrlist = pango_attr_list_new();

    pango_attr_list_insert(attrlist, out->shortcut_underline);

    pango_layout_set_attributes(out->layout, attrlist);
    pango_attr_list_unref(attrlist);

    switch (weight) {
    case RR_FONTWEIGHT_LIGHT:     pweight = PANGO_WEIGHT_LIGHT;     break;
    case RR_FONTWEIGHT_NORMAL:    pweight = PANGO_WEIGHT_NORMAL;    break;
    case RR_FONTWEIGHT_SEMIBOLD:  pweight = PANGO_WEIGHT_SEMIBOLD;  break;
    case RR_FONTWEIGHT_BOLD:      pweight = PANGO_WEIGHT_BOLD;      break;
    case RR_FONTWEIGHT_ULTRABOLD: pweight = PANGO_WEIGHT_ULTRABOLD; break;
    default: g_assert_not_reached();
    }

    switch (slant) {
    case RR_FONTSLANT_NORMAL:  pstyle = PANGO_STYLE_NORMAL;    break;
    case RR_FONTSLANT_ITALIC:  pstyle = PANGO_STYLE_ITALIC;    break;
    case RR_FONTSLANT_OBLIQUE: pstyle = PANGO_STYLE_OBLIQUE;   break;
    default: g_assert_not_reached();
    }


    pango_font_description_set_family(out->font_desc, name);
    pango_font_description_set_weight(out->font_desc, pweight);
    pango_font_description_set_style(out->font_desc, pstyle);
    pango_font_description_set_size(out->font_desc, size * PANGO_SCALE);


    pango_layout_set_font_description(out->layout, out->font_desc);
    pango_layout_set_wrap(out->layout, PANGO_WRAP_WORD_CHAR);


    measure_font(inst, out);

    return out;
}
