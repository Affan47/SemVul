os_basename(string_ty *name, string_ty *ext)
{
    trace(("os_basename(name =\"%s\", ext = \"%s\")\n{\n", name->str_text,
           (ext ? ext->str_text : "(null)")));
    const char *cp = strrchr(name->str_text, '/');
    if (cp)
	++cp;
    else
	cp = name->str_text;

    const char *ep = name->str_text + name->str_length;
    if (NULL != ext && str_trailing_suffix(name, ext))
	ep -= ext->str_length;

    string_ty *path = str_n_from_c(cp, ep - cp);
    trace_string(path->str_text);
    trace(("}\n"));
    return path;
}
