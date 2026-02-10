halfdelay(int t)
{
    T((T_CALLED("halfdelay(%d)"), t));

    if (t < 1 || t > 255 || SP == 0)
	returnCode(ERR);

    cbreak();
    SP->_cbreak = t + 1;
    returnCode(OK);
}
