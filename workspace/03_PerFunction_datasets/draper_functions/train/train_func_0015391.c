dc1394_avt_get_aoi(dc1394camera_t *camera,
                   dc1394bool_t *on_off, int *left, int *top, int *width, int *height)
{
    dc1394error_t err;
    uint32_t value;


    err=dc1394_get_adv_control_register(camera,REG_CAMERA_AVT_AUTOFNC_AOI, &value);
    DC1394_ERR_RTN(err,"Could not get AVT autofocus AOI");


    *on_off = (uint32_t)((value & 0x2000000UL) >> 25);


    err=dc1394_get_adv_control_register(camera,REG_CAMERA_AVT_AF_AREA_SIZE, &value);
    DC1394_ERR_RTN(err,"Could not get AVT AF area size");


    *width =(uint32_t)(value >> 16);

    *height =(uint32_t)(value & 0xFFFFUL );


    err=dc1394_get_adv_control_register(camera,REG_CAMERA_AVT_AF_AREA_POSITION, &value);
    DC1394_ERR_RTN(err,"Could not get AVT AF area position");


    *left =(uint32_t)(value >> 16);

    *top =(uint32_t)(value & 0xFFFFUL );

    return DC1394_SUCCESS;
}
