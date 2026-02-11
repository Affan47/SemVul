vim_backtick(p)
    char_u	*p;
{
    return (*p == '`' && *(p + 1) != NUL && *(p + STRLEN(p) - 1) == '`');
}
