drv_CF_GPO(const int num, const int val)
{
    static unsigned char PWM2[4] = { 0, 0, 0, 0 };
    static unsigned char PWM3[2];

    int v = val;

    if (v < 0)
	v = 0;
    if (v > 100)
	v = 100;

    switch (Protocol) {
    case 2:
	PWM2[num] = v;
	drv_CF_send(17, 4, PWM2);
	break;
    case 3:
	PWM3[0] = num + 1;
	PWM3[1] = v;
	drv_CF_send(34, 2, PWM3);
	break;
    }

    return v;
}
