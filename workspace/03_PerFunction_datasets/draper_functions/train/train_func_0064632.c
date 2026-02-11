line_uniq(char * text, char breakchar) {
    char ** lines;
    int linenum = line_tok(text, &lines, breakchar);
    int i;
    strcpy(text, lines[0]);
    for ( i = 1; i < linenum; i++ ) {
        int dup = 0;
        for (int j = 0; j < i; j++) {
            if (strcmp(lines[i], lines[j]) == 0) dup = 1;
        }
        if (!dup) {
            if ((i > 1) || (*(lines[0]) != '\0')) {
                sprintf(text + strlen(text), "%c", breakchar);
            }
            strcat(text, lines[i]);
        }
    }
    for ( i = 0; i < linenum; i++ ) {
        if (lines[i]) free(lines[i]);
    }
    if (lines) free(lines);
    return text;
}
