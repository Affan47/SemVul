uc_strcpy(unichar_t *to, const char *from) {
    register unichar_t ch;
    while ( (ch = *(unsigned char *) from++) != '\0' )
	*(to++) = ch;
    *to = 0;
}
