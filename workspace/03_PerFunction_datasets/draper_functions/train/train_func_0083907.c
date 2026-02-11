s_puts_to_buffer(char *str)
{
    static int idx = 0;
    int len;


    if (str == NULL) {
	idx = 0;
	return;
    }

    len = strlen(str);
    if (idx + len >= sizeof(cell_buffer_for_print)) {


	idx = sizeof(cell_buffer_for_print);
    } else {
	strcpy(cell_buffer_for_print + idx, str);
	idx += len;
    }
}
