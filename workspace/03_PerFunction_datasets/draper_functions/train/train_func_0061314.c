dc1394_avt_set_shading(dc1394camera_t *camera,
                       dc1394bool_t on_off, dc1394bool_t compute,
                       dc1394bool_t show, uint32_t frame_nb)
{
    dc1394error_t err;
    uint32_t curval;


    err=dc1394_get_adv_control_register(camera,REG_CAMERA_AVT_SHDG_CTRL, &curval);
    DC1394_ERR_RTN(err,"Could not get AVT shading control reg");


    curval = (curval & 0xFDFFFFFFUL) | ((on_off ) << 25);


    curval = (curval & 0xFBFFFFFFUL) | ((compute ) << 26);


    curval = (curval & 0xF7FFFFFFUL) | ((show ) << 27);


    curval = (curval & 0xFFFFFF00UL) | ((frame_nb & 0xFFUL ));


    err=dc1394_set_adv_control_register(camera,REG_CAMERA_AVT_SHDG_CTRL, curval);
    DC1394_ERR_RTN(err,"Could not set AVT shading control reg");

    return DC1394_SUCCESS;

}
