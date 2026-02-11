Scm_GetStringContent(ScmString *str,
                                 unsigned int *psize,
                                 unsigned int *plength,
                                 unsigned int *pflags)
{
    const ScmStringBody *b = SCM_STRING_BODY(str);
    if (psize)   *psize = SCM_STRING_BODY_SIZE(b);
    if (plength) *plength = SCM_STRING_BODY_LENGTH(b);
    if (pflags) *pflags = SCM_STRING_BODY_FLAGS(b);
    return get_string_from_body(b);
}
