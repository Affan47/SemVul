dc1394_format7_set_image_position(dc1394camera_t *camera,
                                  dc1394video_mode_t video_mode, uint32_t left,
                                  uint32_t top)
{
    dc1394error_t err=_dc1394_format7_set_image_position(camera, video_mode, left, top);
    DC1394_ERR_RTN(err, "Format7 image position setting failure");


    err=_dc1394_v130_handshake(camera, video_mode);
    DC1394_ERR_RTN(err, "F7 handshake failure");

    return err;
}
