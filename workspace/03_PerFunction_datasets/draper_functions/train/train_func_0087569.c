dc1394_video_set_multi_shot(dc1394camera_t *camera, uint32_t numFrames, dc1394switch_t pwr)
{
    dc1394error_t err;
    switch (pwr) {
    case DC1394_ON:
        err=dc1394_set_control_register(camera, REG_CAMERA_ONE_SHOT, (0x40000000UL | (numFrames & 0xFFFFUL)));
        DC1394_ERR_RTN(err, "Could not set multishot");
        break;
    case DC1394_OFF:
        err=dc1394_video_set_one_shot(camera,pwr);
        DC1394_ERR_RTN(err, "Could not unset multishot");
        break;
    default:
        err=DC1394_INVALID_ARGUMENT_VALUE;
        DC1394_ERR_RTN(err, "Invalid switch value");
    }
    return err;
}
