slk_touch(void)
{
    T((T_CALLED("slk_touch()")));

    if (SP == NULL || SP->_slk == NULL)
	returnCode(ERR);
    SP->_slk->dirty = TRUE;

    returnCode(OK);
}
