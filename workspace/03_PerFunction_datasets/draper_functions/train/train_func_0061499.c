dc1394_set_absolute_register(dc1394camera_t *camera, unsigned int feature,
        uint64_t offset, uint32_t value)
{
    uint64_t absoffset;
    if (camera == NULL)
        return DC1394_CAMERA_NOT_INITIALIZED;

    QueryAbsoluteCSROffset(camera, feature, &absoffset);

    return dc1394_set_registers (camera, absoffset + offset, &value, 1);
}
