gx_num_components_Pattern(const gs_color_space * pcs)
{
    return
        (pcs->params.pattern.has_base_space ?
         -1 - cs_num_components(pcs->base_space) :
         -1  );
}
