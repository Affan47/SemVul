itoa(int integer) {
	int tmp = integer;
	int size;
	char *result;

	if(integer == 0)
		size = 2;
	else if(integer < 0)
		size = 2;
	else if(integer > 0)
		size = 1;

	while(tmp) {
		tmp /= 10;
		size++;
	}

	result = malloc(size);
	snprintf(result, size, "%i", integer);
	return result;
}
