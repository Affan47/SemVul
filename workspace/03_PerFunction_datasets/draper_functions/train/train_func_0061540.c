fl_xyplot_w2s( FL_OBJECT * ob,
               double      wx,
               double      wy,
               float     * sx,
               float     * sy )
{
    FLI_XYPLOT_SPEC *sp = ob->spec;

    if ( sp->xscale == FL_LOG )
        *sx = log10( wx ) / sp->lxbase * sp->ax + sp->bxm + 0.5;
    else
        *sx = wx * sp->ax + sp->bxm + 0.5;

    if ( sp->yscale == FL_LOG )
        *sy = log10( wy ) / sp->lybase * sp->ay + sp->bym + 0.5;
    else
        *sy = wy * sp->ay + sp->bym + 0.5;
}
