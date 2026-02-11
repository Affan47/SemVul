print_apps(FILE* f) {
    DB_APP app;
    fprintf(f, "    <applications>\n");
    while (!app.enumerate()) {
        print_app(f, app);
    }
    fprintf(f, "    </applications>\n");
    return 0;
}
