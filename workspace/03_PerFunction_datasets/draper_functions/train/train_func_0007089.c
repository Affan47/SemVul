parse_argument(char* text, struct beeversion *versionsnummer)
{
    int p;

    if((p=parse_version(text, versionsnummer))) {
        fprintf(stderr, "beeversion: syntax error at position %d in '%s'\n", p, text);
        return(0);
    }
    return(1);
}
