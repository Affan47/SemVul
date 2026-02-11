dc1394_avt_get_lut_mem_ctrl(dc1394camera_t *camera, dc1394bool_t *en_write,
                            uint32_t * AccessLutNo,uint32_t *addroffset)
{
    dc1394error_t err;
    uint32_t value;


    err=dc1394_get_adv_control_register(camera,REG_CAMERA_AVT_LUT_MEM_CTRL, &value);
    DC1394_ERR_RTN(err,"Could not get AVT LUT memory control");


    *en_write = (uint32_t)((value & 0x4000000UL) >> 26);


    *AccessLutNo=(uint32_t)((value >> 16) & 0xFFUL);


    *addroffset =(uint32_t)((value & 0xFFFFUL));

    return DC1394_SUCCESS;
}
