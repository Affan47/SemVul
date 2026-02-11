df_trigger_cmp_lwsp(char *s1, char *s2)
{
    while(*s1 && isspace((unsigned char)*s1))
      s1++;

    return((*s1) ? (!strncmp(s1, s2, strlen(s2)) ? 1 : -1) : 0);
}
