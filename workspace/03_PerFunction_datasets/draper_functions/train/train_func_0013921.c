rss_skip_whitespace(char *s)
{
    for(; *s && isspace((unsigned char) *s); s++)
      ;

    return(s);
}
