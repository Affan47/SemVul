str_matcher(const mhReqMatcherBldr_t *mp, const char *actual)
{
    const char *expected = mp->baton;

    if (expected == actual)
        return YES;

    if ((!expected && *actual == '\0') ||
        (!actual && *expected == '\0'))
        return YES;

    if (expected && actual && strcmp(expected, actual) == 0)
        return YES;

    return NO;
}
