dns_util_is_greater_serial(uint32_t serial, uint32_t serial_orig)
{


    if ((serial < serial_orig && serial_orig - serial > 2147483648U) ||
        (serial > serial_orig && serial - serial_orig < 2147483648U)) {
        return 1;
    }

    return 0;
}
