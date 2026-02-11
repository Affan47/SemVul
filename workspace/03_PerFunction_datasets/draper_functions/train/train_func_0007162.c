dc1394_basler_sff_feature_is_enabled (dc1394camera_t* camera, dc1394basler_sff_feature_t feature_id, dc1394bool_t *is_enabled)
{
    const sff_feature *feature_desc = NULL;
    uint64_t feature_address;
    uint32_t data;
    dc1394error_t err;

    if (camera == NULL || is_enabled == NULL) {
        err = DC1394_INVALID_ARGUMENT_VALUE;
        DC1394_ERR_RTN(err, "camera or is_enabled is NULL");
    }

    feature_desc = basler_sff_registry_find_by_id (feature_id);
    if (feature_desc == NULL)
        return DC1394_FAILURE;


    if (!feature_desc->generic) {
        err = DC1394_FUNCTION_NOT_SUPPORTED;
        DC1394_ERR_RTN(err, "cannot check feature with the generic enable function");
    }

    err = get_sff_address_from_csr_guid (camera, &(feature_desc->csr_guid), &feature_address);
    DC1394_ERR_RTN(err, "Cannot get SFF address from GUID");

    if (feature_address == 0)
        return DC1394_FAILURE;

    err = dc1394_get_register (camera, feature_address, &data);
    DC1394_ERR_RTN(err, "Cannot read SFF feature CSR register");


    if (data & BASLER_SFF_CSR_BIT_ENABLE) {
        *is_enabled = DC1394_TRUE;
    } else {
        *is_enabled = DC1394_FALSE;
    }
    return DC1394_SUCCESS;
}
