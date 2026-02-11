gf_wrap_filter_opt(int width, int width_max, int *margin, int indent, int flags)
{
    WRAP_S *wrap;


    wrap = (WRAP_S *) fs_get(sizeof(WRAP_S));
    memset(wrap, 0, sizeof(WRAP_S));
    wrap->wrap_col     = width;
    wrap->wrap_max     = width_max;
    wrap->indent       = indent;
    wrap->margin_l     = (margin) ? margin[0] : 0;
    wrap->margin_r     = (margin) ? margin[1] : 0;
    wrap->tags	       = (GFW_HANDLES & flags) == GFW_HANDLES;
    wrap->on_comma     = (GFW_ONCOMMA & flags) == GFW_ONCOMMA;
    wrap->flowed       = (GFW_FLOWED & flags) == GFW_FLOWED;
    wrap->leave_flowed = (GFW_FLOW_RESULT & flags) == GFW_FLOW_RESULT;
    wrap->delsp	       = (GFW_DELSP & flags) == GFW_DELSP;
    wrap->use_color    = (GFW_USECOLOR & flags) == GFW_USECOLOR;
    wrap->hdr_color    = (GFW_HDRCOLOR & flags) == GFW_HDRCOLOR;
    wrap->for_compose  = (GFW_FORCOMPOSE & flags) == GFW_FORCOMPOSE;
    wrap->handle_soft_hyphen = (GFW_SOFTHYPHEN & flags) == GFW_SOFTHYPHEN;

    return((void *) wrap);
}
