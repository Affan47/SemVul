DefinedColor(char *name) {
    if (colors == 0 || colorCount == 0)
        return 0;
    for (int i = 0; i < colorCount; i++)
        if (strcmp(name, colors[i].colorName) == 0)
            return colors[i].colorValue;
    return 0;
}
