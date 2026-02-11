slk_attrset(const chtype attr)
{
    T((T_CALLED("slk_attrset(%s)"), _traceattr(attr)));

    if (SP != 0 && SP->_slk != 0) {
	SetAttr(SP->_slk->attr, attr);
	returnCode(OK);
    } else
	returnCode(ERR);
}
