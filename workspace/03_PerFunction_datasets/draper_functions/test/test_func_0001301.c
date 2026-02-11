gs_shading_Tpp_init(gs_shading_t ** ppsh,
                  const gs_shading_Tpp_params_t * params, gs_memory_t * mem)
{
    gs_shading_Tpp_t *psh;
    int code = check_mesh((const gs_shading_mesh_params_t *)params);
    int bpf = check_BPF(&params->DataSource, params->BitsPerFlag);

    if (code < 0)
        return code;
    if (bpf < 0)
        return bpf;
    ALLOC_SHADING(&st_shading_Tpp, shading_type_Tensor_product_patch,
                  shading_Tpp_procs, "gs_shading_Tpp_init");
    psh->params.BitsPerFlag = bpf;
    return 0;
}
