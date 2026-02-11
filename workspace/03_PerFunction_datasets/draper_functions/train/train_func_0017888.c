parseNumber(char **s) {


	u_int32_t value=0;

	if (!isDigit(**s)) return -1;

	while(isDigit(**s)) {
		value=value*10 + **s -'0';
		(*s)++;
	}

	return value;
}
