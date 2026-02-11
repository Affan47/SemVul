process(void)
{
    char buf[MAX_LINELEN+1];
    int c;
    do {
	c=ggetline(buf); obj_main(buf);
    }
    while(c!=EOF);
}
