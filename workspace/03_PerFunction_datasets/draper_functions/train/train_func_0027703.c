beep(void)
{
    int res = ERR;

    T((T_CALLED("beep()")));


    if (cur_term == 0) {
	res = ERR;
    } else if (bell) {
	TPUTS_TRACE("bell");
	res = putp(bell);
	_nc_flush();
    } else if (flash_screen) {
	TPUTS_TRACE("flash_screen");
	res = putp(flash_screen);
	_nc_flush();
    }

    returnCode(res);
}
