OutputEncodedString(const unsigned char* str)
{

	while (*str != 0)
	{
		if ((*str < 0x20) || (*str > 0x7F))
		{

			printf("&#x%02x;", *str);
		}
		else
		{
			switch (*str)
			{
				case '<':
				case '>':
				case '&':
				case '\'':
				case '\"':

					printf("&#x%2x", *str);
					break;

				default:
					printf("%c", *str);
					break;
			}
		}

		str++;
	}
}
