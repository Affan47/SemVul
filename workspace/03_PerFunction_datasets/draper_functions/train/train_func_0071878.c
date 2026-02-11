simple_ttgetc(int (*recorder)(int), void (*bail_handler)(void))
{
    int		  res;
    unsigned char c;

    while((res = read(STDIN_FD, &c, 1)) <= 0)
      if(!(res < 0 && errno == EINTR))
	(*bail_handler)();

    return(recorder ? (*recorder)((int)c) : (int)c);
}
