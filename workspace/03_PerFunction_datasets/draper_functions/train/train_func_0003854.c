get_op_type(char1, char2)
    int		char1;
    int		char2;
{
    int		i;

    if (char1 == 'r')
	return OP_REPLACE;
    if (char1 == '~')
	return OP_TILDE;
    for (i = 0; ; ++i)
	if (opchars[i][0] == char1 && opchars[i][1] == char2)
	    break;
    return i;
}
