dirname()
    const
{
    const char *cp = c_str();
    const char *ep = strrchr(cp, '/');
    if (!ep)
        return ".";
    if (ep == cp)
        return "/";
    return nstring(cp, ep - cp);
}
