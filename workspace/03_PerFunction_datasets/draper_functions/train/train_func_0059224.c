dc1394_avt_set_channel_adjust(dc1394camera_t *camera, int16_t channel_adjust)
{
    dc1394error_t err;


    err=dc1394_set_adv_control_register(camera,REG_CAMERA_AVT_CHANNEL_ADJUST_VALUE, (uint32_t)channel_adjust);
    DC1394_ERR_RTN(err,"Could not set AVT channel adjust");

    return DC1394_SUCCESS;
}
