dc1394_memory_load(dc1394camera_t *camera, uint32_t channel)
{
    dc1394error_t err=dc1394_set_control_register(camera, REG_CAMERA_CUR_MEM_CH, (uint32_t)((channel & 0xFUL) << 28));
    DC1394_ERR_RTN(err, "Could not load from memory");
    return err;
}
