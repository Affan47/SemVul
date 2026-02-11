kptr_print(const atm_kptr_t *p)
{
    static char buf[KPRT_PRINT_BUFS][sizeof(atm_kptr_t)*2+1];
    static int curr_buf = 0;
    char *result;
    int i;

    result = buf[curr_buf];
    curr_buf = (curr_buf+1) & (KPRT_PRINT_BUFS-1);
    for (i = 0; i < sizeof(atm_kptr_t); i++)
	sprintf(result+2*i,"%02x",((unsigned char *) p)[i]);
    return result;
}
