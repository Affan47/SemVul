quote_length(const char *line)
{
#ifdef HAVE_REGEX_H
    regmatch_t matches;
    int rc = regexec(&quotereg, line, 1, &matches, 0);

    if (rc == REG_NOMATCH || matches.rm_so == (regoff_t)-1)
	return 0;


    return matches.rm_eo;
#else
    size_t qdepth = 0;


    while (strncmp(line + qdepth, quotestr, quotelen) == 0)
	qdepth += quotelen;
    return qdepth;
#endif
}
