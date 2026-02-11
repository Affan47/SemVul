sqlippool_expand(char * out, int outlen, const char * fmt,
			    rlm_sqlippool_t *data, char * param, int param_len)
{
	char *q;
	const char *p;
	char tmp[40];

	q = out;
	for (p = fmt; *p ; p++) {
		int freespace;
		int c;


		freespace = outlen - (q - out);
		if (freespace <= 1)
			break;

		c = *p;
		if (c != '%' && c != '$' && c != '\\') {
			*q++ = *p;
			continue;
		}

		if (*++p == '\0')
			break;

		if (c == '\\') {
			switch(*p) {
			case '\\':
				*q++ = '\\';
				break;
			case 't':
				*q++ = '\t';
				break;
			case 'n':
				*q++ = '\n';
				break;
			default:
				*q++ = c;
				*q++ = *p;
				break;
			}
		}
		else if (c == '%') {
			switch(*p) {
			case '%':
				*q++ = *p;
				break;
			case 'P':
				strlcpy(q, data->pool_name, freespace);
				q += strlen(q);
				break;
			case 'I':
				if (param && param_len > 0) {
					if (param_len > freespace) {
						strlcpy(q, param, freespace);
						q += strlen(q);
					}
					else {
						memcpy(q, param, param_len);
						q += param_len;
					}
				}
				break;
			case 'J':
				sprintf(tmp, "%d", data->lease_duration);
				strlcpy(q, tmp, freespace);
				q += strlen(q);
				break;
			default:
				*q++ = '%';
				*q++ = *p;
				break;
			}
		}
	}
	*q = '\0';

#if 0
	DEBUG2("sqlippool_expand: '%s'", out);
#endif

	return strlen(out);
}
