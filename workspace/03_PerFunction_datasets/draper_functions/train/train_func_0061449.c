drv_HD_PP_stop(void)
{

    if (Bits == 8) {
	drv_generic_parport_control(SIGNAL_RS |
				    SIGNAL_RW | SIGNAL_ENABLE | SIGNAL_ENABLE2 | SIGNAL_ENABLE3 | SIGNAL_ENABLE4 |
				    SIGNAL_BACKLIGHT | SIGNAL_GPO, 0);
    } else {
	drv_generic_parport_data(0 ^ invert_data_bits);
	drv_generic_parport_control(SIGNAL_BACKLIGHT | SIGNAL_GPO | SIGNAL_POWER, 0);
    }

    drv_generic_parport_close();

}
