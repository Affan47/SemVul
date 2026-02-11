dc1394_pxl_get_camera_serial_number(dc1394camera_t *camera, uint32_t *serial_num_int)
{
    if (camera == NULL)
        return DC1394_FAILURE;

    uint32_t serial_num_offset, serial_num_length;
    dc1394_get_adv_control_register(camera, PxL_ACR_SERIAL_NUM_OFFSET,
                                    &serial_num_offset);
    dc1394_get_adv_control_register(camera, PxL_ACR_SERIAL_NUM_LENGTH,
                                    &serial_num_length);

    char *serial_num = (char *) malloc((serial_num_length/4+1)*4);
    dc1394_pxl_read_n_bytes(camera, serial_num_offset, serial_num, serial_num_length);
    *serial_num_int = atoi(serial_num);
    free(serial_num);

    return DC1394_SUCCESS;
}
