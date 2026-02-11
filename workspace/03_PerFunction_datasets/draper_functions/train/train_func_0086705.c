_xmlSchemaParseTime (xmlSchemaValDatePtr dt, const xmlChar **str) {
    const xmlChar *cur = *str;
    int ret = 0;
    int value = 0;

    PARSE_2_DIGITS(value, cur, ret);
    if (ret != 0)
        return ret;
    if (*cur != ':')
        return 1;
    if (!VALID_HOUR(value))
        return 2;
    cur++;


    dt->hour = value;

    PARSE_2_DIGITS(value, cur, ret);
    if (ret != 0)
        return ret;
    if (!VALID_MIN(value))
        return 2;
    dt->min = value;

    if (*cur != ':')
        return 1;
    cur++;

    PARSE_FLOAT(dt->sec, cur, ret);
    if (ret != 0)
        return ret;

    if ((!VALID_SEC(dt->sec)) || (!VALID_TZO(dt->tzo)))
        return 2;

    *str = cur;
    return 0;
}
