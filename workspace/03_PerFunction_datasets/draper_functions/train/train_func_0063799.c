mangleSignature(MethodBlock *mb) {
    char *type = mb->type;
    char *nonMangled;
    char *mangled;
    int i;


    for(i = strlen(type) - 1; type[i] != ')'; i--);

    nonMangled = sysMalloc(i);
    strncpy(nonMangled, type + 1, i - 1);
    nonMangled[i - 1] = '\0';

    mangled = mangleString(nonMangled);
    sysFree(nonMangled);
    return mangled;
}
