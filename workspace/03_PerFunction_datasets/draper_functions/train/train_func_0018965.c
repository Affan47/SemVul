line_type(const char *line)
{
    const char *p;
    if (startswith(line, "%%BeginFeature:"))
        return LT_BEGIN_FEATURE;
    p = line;
    while (*p && isspace(*p)) p++;
    if (!startswith(p, "%%"))
        return 0;
    p += 2;
    while (*p && isspace(*p)) p++;
    if (startswith(p, "FoomaticRIPOptionSetting:"))
        return LT_FOOMATIC_RIP_OPTION_SETTING;
    return 0;
}
