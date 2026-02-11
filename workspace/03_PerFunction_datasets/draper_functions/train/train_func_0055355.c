hash(const char * word)
{
    int i;
    long  hv = 0;
    for (i=0; i < 4  &&  *word != 0; i++)
	hv = (hv << 8) | (*word++);
    while (*word != 0) {
      ROTATE(hv,ROTATE_LEN);
      hv ^= (*word++);
    }
    return (unsigned long) hv % tablesize;
}
