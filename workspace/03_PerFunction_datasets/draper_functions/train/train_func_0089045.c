dict_status_p(const char *status)
{
    return in_level > 3
	&& memcmp(in_buffer, status, 3) == 0
	&& (in_buffer[3] == ' '
	    || (in_level == 5 && memcmp(in_buffer+3,"\r\n",2) == 0));
}
