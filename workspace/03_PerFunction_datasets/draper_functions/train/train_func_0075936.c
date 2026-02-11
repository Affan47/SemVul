loadFiles()
{


    string loadfile = "/etc/cygnalrc";
    parseFile(loadfile);


    loadfile = "/usr/local/etc/cygnalrc";
    parseFile(loadfile);


    char *home = getenv("HOME");
    if (home) {
        loadfile = home;
        loadfile += "/.cygnalrc";
        parseFile(loadfile);
    }


    char *cygnalrc = getenv("CYGNALRC");
    if (cygnalrc) {
        loadfile = cygnalrc;
        return parseFile(loadfile);
    }

    return false;
}
