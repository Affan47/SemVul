secu_ClearPassword(char *p)
{
    if (p) {
	PORT_Memset(p, 0, PORT_Strlen(p));
	PORT_Free(p);
    }
}
