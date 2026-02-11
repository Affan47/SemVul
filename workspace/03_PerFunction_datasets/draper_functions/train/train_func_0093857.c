pdf_finish_cie_space(cos_array_t *pca, cos_dict_t *pcd,
                     const gs_cie_common *pciec)
{
    int code = cos_dict_put_c_key_vector3(pcd, "/WhitePoint",
                                          &pciec->points.WhitePoint);

    if (code < 0)
        return code;
    if (pciec->points.BlackPoint.u != 0 ||
        pciec->points.BlackPoint.v != 0 ||
        pciec->points.BlackPoint.w != 0
        ) {
        code = cos_dict_put_c_key_vector3(pcd, "/BlackPoint",
                                          &pciec->points.BlackPoint);
        if (code < 0)
            return code;
    }
    return cos_array_add_object(pca, COS_OBJECT(pcd));
}
