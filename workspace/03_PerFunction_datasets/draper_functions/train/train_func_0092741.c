keybound(int code, int count)
{
    char *result = 0;

    T((T_CALLED("keybound(%d,%d)"), code, count));
    if (SP != 0 && code >= 0) {
	result = _nc_expand_try(SP->_keytry, (unsigned) code, &count, 0);
    }
    returnPtr(result);
}
