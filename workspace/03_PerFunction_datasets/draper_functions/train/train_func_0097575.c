dc1394_external_trigger_get_source(dc1394camera_t *camera, dc1394trigger_source_t *source)
{
    uint32_t value;
    dc1394error_t err= dc1394_get_control_register(camera, REG_CAMERA_TRIGGER_MODE, &value);
    DC1394_ERR_RTN(err, "Could not get trigger source");

    *source= (uint32_t)( ((value >> 21) & 0x7UL) );
    if (*source > 3)
        *source -= 3;
    (*source)+= DC1394_TRIGGER_SOURCE_MIN;

    return err;
}
