dc1394_feature_get_modes(dc1394camera_t *camera, dc1394feature_t feature, dc1394feature_modes_t *modes)
{
    dc1394error_t err;
    uint64_t offset;
    uint32_t quadval;

    modes->num=0;

    if ( (feature<DC1394_FEATURE_MIN) || (feature>DC1394_FEATURE_MAX) )
        return DC1394_INVALID_FEATURE;

    if (feature == DC1394_FEATURE_TRIGGER) {
        return DC1394_SUCCESS;
    }

    FEATURE_TO_INQUIRY_OFFSET(feature, offset);

    err=dc1394_get_control_register(camera, offset, &quadval);
    DC1394_ERR_RTN(err, "Could not get mode availability for feature");

    if (quadval & 0x01000000UL) {
        modes->modes[modes->num]=DC1394_FEATURE_MODE_MANUAL;
        modes->num++;
    }
    if (quadval & 0x02000000UL) {
        modes->modes[modes->num]=DC1394_FEATURE_MODE_AUTO;
        modes->num++;
    }
    if (quadval & 0x10000000UL) {
        modes->modes[modes->num]=DC1394_FEATURE_MODE_ONE_PUSH_AUTO;
        modes->num++;
    }

    return err;
}
