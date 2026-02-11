my_cfg(RESULT * result, const int argc, RESULT * argv[])
{
    int i, len;
    char *value;
    char *buffer;


    len = 0;
    for (i = 0; i < argc; i++) {
	len += strlen(R2S(argv[i])) + 1;
    }


    buffer = malloc(len + 1);


    *buffer = '\0';
    for (i = 0; i < argc; i++) {
	strcat(buffer, ".");
	strcat(buffer, R2S(argv[i]));
    }


    value = cfg_get("", buffer + 1, "");


    SetResult(&result, R_STRING, value);


    free(buffer);

    free(value);
}
