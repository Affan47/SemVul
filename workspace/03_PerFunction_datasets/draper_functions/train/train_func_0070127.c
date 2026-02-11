set_custom_speed(int speed, int port_fd)
{

    struct serial_struct ser;
    int arby;

    ioctl(port_fd, TIOCGSERIAL, &ser);
    ser.custom_divisor = ser.baud_base / speed;
    if(!(ser.custom_divisor))
	ser.custom_divisor = 1;

    arby = ser.baud_base / ser.custom_divisor;
    ser.flags &= ~ASYNC_SPD_MASK;
    ser.flags |= ASYNC_SPD_CUST;

    ioctl(port_fd, TIOCSSERIAL, &ser);

    return 0;
}
