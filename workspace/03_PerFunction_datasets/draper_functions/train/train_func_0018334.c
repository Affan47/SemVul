so_file_puts(STORE_S *so, char *s)
{
    int rv = *s ? 0 : 1;

    if(!rv && (so->txt || so_reaquire(so)))
      do
	rv = fwrite(s, strlen(s)*sizeof(char), (size_t)1, (FILE *)so->txt);
      while(!rv && ferror((FILE *)so->txt) && errno == EINTR);

    return(rv);
}
