atox(char *s)
{
	int i = 0, ret = 0;

	while(s[i] != '\0') {
		ret <<= 4;
		if((s[i] <= 'F') && (s[i] >= 'A'))
			ret |= s[i] - 'A' + 10;
		else if((s[i] <= 'f') && (s[i] >= 'a'))
			ret |= s[i] - 'a' + 10;
		else if((s[i] <= '9') && (s[i] >= '0'))
			ret |= s[i] - '0';
		i++;
	}
	return(ret);
}
