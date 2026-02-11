drv_BuE_CT_pwm(int val)
{
    static int PWM = -1;
    char cmd[4] = ESC "Adm";


    if (val == -1)
	return PWM;

    if (val < 0)
	val = 0;
    if (val > 255)
	val = 255;
    PWM = val;

    cmd[2] = (char) val;
    cmd[3] = val == 0 ? 1 : 2;
    drv_generic_serial_write(cmd, 4);

    return val;
}
