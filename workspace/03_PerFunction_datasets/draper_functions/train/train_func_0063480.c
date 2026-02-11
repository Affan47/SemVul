initialize_stype3(unsigned char *buf, const size_t num)
{
    int	  i, j;
    stype3 *s_ptr;

    for (i=0; i<(int)num; i++) {
	s_ptr = (stype3*)buf + i;
	s_ptr->a    = i*8+0;
	s_ptr->b    = i*8+1;
        for(j=0; j<8; j++)
	    s_ptr->c[j] = i*8+j;
	s_ptr->d    = i*8+6;
	s_ptr->e    = i*8+7;
    }
}
