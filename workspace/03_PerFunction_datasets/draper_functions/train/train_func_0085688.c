math_cleardiversions(void)
{
	while (oldiostates)
		free(math_getdivertedio());
}
