process_status_code(char * msg)
{
	struct status_code ret;
	int i,j;
	char num[50];
	char * content_len_string;

	for(i = 0; msg[i] != ' '; i++);
	i++;
	for(j = 0; msg[i] != ' '; i++,j++)
		num[j] = msg[i];
	num[j] = '\0';

	ret.status = atoi(num);

	content_len_string = strstr(msg,"Content-Length:");
	if(content_len_string != NULL)
	{
		content_len_string += 16;
		for(i = 0,j = 0; content_len_string[i] != '\n'; i++,j++)
			num[j] = content_len_string[i];

		num[j] = '\0';
		ret.content_length = atoi(num);
		content_len_string = NULL;
		content_len_string = strstr(msg,"<");
		ret.header_length = content_len_string - msg;
	}
	else
	{
		ret.content_length = 0;
		ret.header_length = 0;
	}
	content_len_string = strstr(msg,"Location:");
	if(content_len_string != NULL)
	{
		content_len_string += 9;
		for(i = 0; content_len_string[i] != '\n';i++)
		{
			ret.values[HEADER_LOCATION][i] = content_len_string[i];
		}
		ret.values[HEADER_LOCATION][i] = '\0';
	}


	return ret;
}
