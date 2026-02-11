warning(err_str)
char * err_str;
{
    if (!as_warn.current) return;
    ++totwarn;
    --toterr;
    error(err_str);
}
