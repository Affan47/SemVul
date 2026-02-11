dc1394_video_set_transmission(dc1394camera_t *camera, dc1394switch_t pwr)
{
    dc1394error_t err;

    if (pwr==DC1394_ON) {
        err=dc1394_set_control_register(camera, REG_CAMERA_ISO_EN, DC1394_FEATURE_ON);
        DC1394_ERR_RTN(err, "Could not start ISO transmission");
    }
    else {

        err=dc1394_set_control_register(camera, REG_CAMERA_ISO_EN, DC1394_FEATURE_OFF);
        DC1394_ERR_RTN(err, "Could not stop ISO transmission");
    }

    return err;
}
