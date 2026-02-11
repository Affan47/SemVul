chr_replace(char *str, char search, char replace) {
	unsigned int i=0,j=0;

	while (i < strlen(str)) {
		if (str[i] == search) {
			str[i] = replace;
			j++;
		}
		i++;
	}
	return j;
}
