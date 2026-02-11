newBibCite(char *cite, char *tag)
{
    biblioElem *newCite = newBiblio(cite);
    if (NULL != newCite) {
        newCite->biblioN    = tag;
        newCite->biblioType = BIBLIO_BIBCITE;
        printTable();
    }
    return newCite;
}
