add_tag(const char *token, haskellKind kind, vString *name)
{
    int i;
    for (i = 0; token[i] != '\0'; ++i)
	vStringPut(name, token[i]);

    vStringTerminate(name);
    makeSimpleTag(name, HaskellKinds, kind);
    vStringClear(name);
}
