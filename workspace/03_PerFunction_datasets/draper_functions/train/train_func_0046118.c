set_custom_spec_colors(struct pine *ps)
{
    if(ps->hdr_colors)
      free_spec_colors(&ps->hdr_colors);

    ps->hdr_colors = spec_colors_from_varlist(ps->VAR_VIEW_HDR_COLORS, 1);


    if(ps->kw_colors)
      free_spec_colors(&ps->kw_colors);

    ps->kw_colors = spec_colors_from_varlist(ps->VAR_KW_COLORS, 1);
}
