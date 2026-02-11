dc1394_video_set_iso_speed(dc1394camera_t *camera, dc1394speed_t speed)
{
    dc1394error_t err;
    uint32_t value=0;
    int channel;

    if ((speed>DC1394_ISO_SPEED_MAX) || (speed<DC1394_ISO_SPEED_MIN))
        return DC1394_INVALID_ISO_SPEED;

    err=dc1394_get_control_register(camera, REG_CAMERA_ISO_DATA, &value);
    DC1394_ERR_RTN(err, "Could not get ISO data");


    if ((camera->bmode_capable)&&(value & 0x00008000)) {
        err=dc1394_get_control_register(camera, REG_CAMERA_ISO_DATA, &value);
        DC1394_ERR_RTN(err, "oops");
        channel=(value >> 8) & 0x3FUL;
        err=dc1394_set_control_register(camera, REG_CAMERA_ISO_DATA,
                                        (uint32_t) ( ((channel & 0x3FUL) << 8) | (speed & 0x7UL) | (0x1 << 15) ));
        DC1394_ERR_RTN(err, "oops");
    }
    else {
        if (speed>DC1394_ISO_SPEED_400-DC1394_ISO_SPEED_MIN) {
            dc1394_log_error("An ISO speed >400Mbps was requested while the camera is in LEGACY mode. Please set the operation mode to OPERATION_MODE_1394B before asking for 1394b ISO speeds");
            return DC1394_INVALID_ISO_SPEED;
        }
        err=dc1394_get_control_register(camera, REG_CAMERA_ISO_DATA, &value);
        DC1394_ERR_RTN(err, "oops");
        channel=(value >> 28) & 0xFUL;
        err=dc1394_set_control_register(camera, REG_CAMERA_ISO_DATA,
                                        (uint32_t) (((channel & 0xFUL) << 28) |
                                                    ((speed & 0x3UL) << 24) ));
        DC1394_ERR_RTN(err, "Could not set ISO data register");
    }

    return err;;
}
