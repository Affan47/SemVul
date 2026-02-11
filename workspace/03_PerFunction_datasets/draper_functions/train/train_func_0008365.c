edit_timet (const char *prompt, krb5_timestamp *value, int *mask, int bit)
{
    char buf[1024], resp[1024];

    if (mask && (*mask & bit))
	return 0;

    time_t2str (*value, buf, sizeof (buf), 0);

    for (;;) {
	if(get_response(prompt, buf, resp, sizeof(resp)) != 0)
	    return 1;
	if (parse_timet (resp, value, mask, bit) == 0)
	    break;
    }
    return 0;
}
