handle_unworld_command(String *args, int offset)
{
    World *w;
    int result = 0;
    const char *name;
    char *ptr = args->data + offset;

    while (*(name = stringarg(&ptr, NULL))) {
        if (defaultworld && cstrcmp(name, "default") == 0) {
            free_world(defaultworld);
            defaultworld = NULL;
        } else if ((w = find_world(name))) {
            result += nuke_world(w);
        } else {
            eprintf("No world %s", name);
        }
    }
    return newint(result);
}
