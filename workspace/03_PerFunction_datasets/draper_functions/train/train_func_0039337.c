Digit()
{
	if (LastKeyStruck == '-')
		gather_argument(AS_NEGSIGN, -1);
	else if (jisdigit(LastKeyStruck))
		gather_argument(AS_NUMERIC, LastKeyStruck - '0');
	else
		complain((char *)NULL);
}
