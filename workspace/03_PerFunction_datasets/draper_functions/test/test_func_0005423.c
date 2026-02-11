te_skip_to(TermEnum *te, const char *term)
{
    char *curr_term = te->curr_term;
    if (strcmp(curr_term, term) < 0) {
        while (NULL != ((curr_term = te->next(te)))
               && (strcmp(curr_term, term) < 0)) {
        }
    }
    return curr_term;
}
