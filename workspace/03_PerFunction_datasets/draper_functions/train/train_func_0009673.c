php_charmask(unsigned char *input, int len, char *mask TSRMLS_DC)
{
	unsigned char *end;
	unsigned char c;
	int result = SUCCESS;

	memset(mask, 0, 256);
	for (end = input+len; input < end; input++) {
		c=*input;
		if ((input+3 < end) && input[1] == '.' && input[2] == '.'
				&& input[3] >= c) {
			memset(mask+c, 1, input[3] - c + 1);
			input+=3;
		} else if ((input+1 < end) && input[0] == '.' && input[1] == '.') {


			if (end-len >= input) {
				php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid '..'-range, no character to the left of '..'");
				result = FAILURE;
				continue;
			}
			if (input+2 >= end) {
				php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid '..'-range, no character to the right of '..'");
				result = FAILURE;
				continue;
			}
			if (input[-1] > input[2]) {
				php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid '..'-range, '..'-range needs to be incrementing");
				result = FAILURE;
				continue;
			}

			php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid '..'-range");
			result = FAILURE;
			continue;
		} else {
			mask[c]=1;
		}
	}
	return result;
}
