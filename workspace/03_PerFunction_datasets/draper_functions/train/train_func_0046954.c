generateScaffoldController(HttpRoute *route, int argc, char **argv)
{
    EspRoute    *eroute;
    MprHash     *tokens, *actions;
    cchar       *defines, *name, *path, *data, *title, *action;
    int         i;

    if (app->error) {
        return;
    }
    eroute = route->eroute;
    name = sclone(argv[0]);
    title = spascal(name);
    actions = mprCreateHashFromWords("create destroy edit init list show update");


    path = mprJoinPathExt(mprJoinPath(eroute->controllersDir, name), ".c");
    defines = sclone("");
    for (i = 1; i < argc; i++) {
        action = argv[i];
        if (mprLookupKey(actions, action)) {
            continue;
        }
        defines = sjoin(defines, sfmt("    espDefineAction(eroute, \"%s-%s\", %s);\n", name, action, action), NULL);
    }
    tokens = mprDeserialize(sfmt("{ NAME: %s, TITLE: %s, DEFINE_ACTIONS: '%s' }", name, title, defines));

    data = stemplate(ScaffoldTemplateHeader, tokens);
    for (i = 1; i < argc; i++) {
        action = argv[i];
        if (mprLookupKey(actions, action)) {
            continue;
        }
        data = sjoin(data, sfmt("static void %s() {\n}\n\n", action), NULL);
    }
    data = sjoin(data, stemplate(ScaffoldTemplateFooter, tokens), NULL);
    makeFile(path, data, "Scaffold");
}
