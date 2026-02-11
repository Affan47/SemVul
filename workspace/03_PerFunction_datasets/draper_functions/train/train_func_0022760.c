save_macros(String *args, int offset)
{
    Macro *spec;
    TFILE *file = NULL;
    int result = 1;
    const char *name, *mode = "w";
    char opt, *next;
    int mflag;

    startopt(CS(args), "a");
    while ((opt = nextopt(NULL, NULL, NULL, &offset))) {
        if (opt != 'a') return 0;
        mode = "a";
    }

    next = args->data + offset;
    name = stringarg(&next, NULL);
    offset = next - args->data;
    if (!(spec = macro_spec(args, offset, &mflag, NULL))) result = 0;
    if (result && !(file = tfopen(expand_filename(name), mode))) {
        operror(name);
        result = 0;
    }

    if (result) {
        oprintf("%% %sing macros to %s", *mode=='w' ? "Writ" : "Append",
            file->name);
        result = list_defs(file, spec, mflag, NULL);
    }
    if (file) tfclose(file);
    if (spec) nuke_macro(spec);
    return result;
}
