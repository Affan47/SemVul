dc1394_video_get_iso_speed(dc1394camera_t *camera, dc1394speed_t *speed)
{
    dc1394error_t err;
    uint32_t value;

    err=dc1394_get_control_register(camera, REG_CAMERA_ISO_DATA, &value);
    DC1394_ERR_RTN(err, "Could not get ISO data");

    if (camera->bmode_capable) {
        if (value & 0x00008000) {
            *speed= (uint32_t)(value& 0x7UL);
            if ((*speed<DC1394_ISO_SPEED_MIN)||(*speed>DC1394_ISO_SPEED_MAX))
                return DC1394_INVALID_ISO_SPEED;
        }
        else {
            *speed= (uint32_t)((value >> 24) & 0x3UL);
            if ((*speed<DC1394_ISO_SPEED_MIN)||(*speed>DC1394_ISO_SPEED_400))
                return DC1394_INVALID_ISO_SPEED;
        }
    }
    else {
        *speed= (uint32_t)((value >> 24) & 0x3UL);
        if ((*speed<DC1394_ISO_SPEED_MIN)||(*speed>DC1394_ISO_SPEED_400))
            return DC1394_INVALID_ISO_SPEED;
    }

    return err;
}
