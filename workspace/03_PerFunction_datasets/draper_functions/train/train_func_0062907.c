convert_bdaddr(char *str_bdaddr, char *bdaddr)
{
	char bdbyte[3];
	char *str_byte = str_bdaddr;
	int i, j;
	int colon_present = 0;

	if (strstr(str_bdaddr, ":"))
		colon_present = 1;

	bdbyte[2] = '\0';


	for (i = 0, j = 5; i < 6; i++, j--) {
		bdbyte[0] = str_byte[0];
		bdbyte[1] = str_byte[1];
		bdaddr[j] = strtol(bdbyte, NULL, 16);

		if (colon_present == 1)
			str_byte += 3;
		else
			str_byte += 2;
	}
}
