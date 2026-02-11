generateScaffold(HttpRoute *route, int argc, char **argv)
{
    if (argc < 1) {
        usageError();
        return;
    }
    if (app->error) {
        return;
    }
    generateScaffoldController(route, 1, argv);
    generateScaffoldViews(route, argc, argv);
    generateTable(route, argc, argv);
}
