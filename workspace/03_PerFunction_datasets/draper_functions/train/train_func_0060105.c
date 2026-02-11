gs_cie_render1_init_from(const gs_memory_t *mem,
                         gs_cie_render * pcrd,
                         void *client_data,
                         const gs_cie_render * pfrom_crd,
                         const gs_vector3 * WhitePoint,
                         const gs_vector3 * BlackPoint,
                         const gs_matrix3 * MatrixPQR,
                         const gs_range3 * RangePQR,
                         const gs_cie_transform_proc3 * TransformPQR,
                         const gs_matrix3 * MatrixLMN,
                         const gs_cie_render_proc3 * EncodeLMN,
                         const gs_range3 * RangeLMN,
                         const gs_matrix3 * MatrixABC,
                         const gs_cie_render_proc3 * EncodeABC,
                         const gs_range3 * RangeABC,
                         const gs_cie_render_table_t * RenderTable)
{
    pcrd->id = gs_next_ids(mem, 1);
    pcrd->client_data = client_data;
    pcrd->points.WhitePoint = *WhitePoint;
    pcrd->points.BlackPoint =
        *(BlackPoint ? BlackPoint : &BlackPoint_default);
    pcrd->MatrixPQR = *(MatrixPQR ? MatrixPQR : &Matrix3_default);
    pcrd->RangePQR = *(RangePQR ? RangePQR : &Range3_default);
    pcrd->TransformPQR =
        *(TransformPQR ? TransformPQR : &TransformPQR_default);
    pcrd->MatrixLMN = *(MatrixLMN ? MatrixLMN : &Matrix3_default);
    pcrd->EncodeLMN = *(EncodeLMN ? EncodeLMN : &Encode_default);
    if (pfrom_crd &&
        !memcmp(&pcrd->EncodeLMN, &EncodeLMN_from_cache,
                sizeof(EncodeLMN_from_cache))
        )
        memcpy(&pcrd->caches.EncodeLMN, &pfrom_crd->caches.EncodeLMN,
               sizeof(pcrd->caches.EncodeLMN));
    pcrd->RangeLMN = *(RangeLMN ? RangeLMN : &Range3_default);
    pcrd->MatrixABC = *(MatrixABC ? MatrixABC : &Matrix3_default);
    pcrd->EncodeABC = *(EncodeABC ? EncodeABC : &Encode_default);
    if (pfrom_crd &&
        !memcmp(&pcrd->EncodeABC, &EncodeABC_from_cache,
                sizeof(EncodeABC_from_cache))
        )
        memcpy(pcrd->caches.EncodeABC, pfrom_crd->caches.EncodeABC,
               sizeof(pcrd->caches.EncodeABC));
    pcrd->RangeABC = *(RangeABC ? RangeABC : &Range3_default);
    if (RenderTable) {
        pcrd->RenderTable = *RenderTable;
        if (pfrom_crd &&
            !memcmp(&pcrd->RenderTable.T, &RenderTableT_from_cache,
                    sizeof(RenderTableT_from_cache))
            ) {
            memcpy(pcrd->caches.RenderTableT, pfrom_crd->caches.RenderTableT,
                   sizeof(pcrd->caches.RenderTableT));
            pcrd->caches.RenderTableT_is_identity =
                pfrom_crd->caches.RenderTableT_is_identity;
        }
    } else {
        pcrd->RenderTable.lookup.table = 0;
        pcrd->RenderTable.T = RenderTableT_default;
    }
    pcrd->status = CIE_RENDER_STATUS_BUILT;
    return 0;
}
