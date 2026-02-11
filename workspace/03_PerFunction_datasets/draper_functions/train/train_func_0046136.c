findfont (char *name) {
    char *font;

    if (name[0] == '\000' || strcmp (name, "default") == 0)
        font = "Times-Roman";
    else
        font = name;
    return font;
}
