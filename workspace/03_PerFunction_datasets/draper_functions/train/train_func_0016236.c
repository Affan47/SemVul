sql_escape_func(char *out, size_t outlen, const char *in)
{
	size_t len = 0;

	while (in[0]) {


		if ((in[0] < 32) ||
		    strchr(allowed_chars, *in) == NULL) {


			if (outlen <= 3) {
				break;
			}

			snprintf(out, outlen, "=%02X", (unsigned char) in[0]);
			in++;
			out += 3;
			outlen -= 3;
			len += 3;
			continue;
		}


		if (outlen <= 1) {
			break;
		}


		*out = *in;
		out++;
		in++;
		outlen--;
		len++;
	}
	*out = '\0';
	return len;
}
