spannq_to_s(Query *self, const char *field)
{
    int i;
    SpanNearQuery *snq = SpNQ(self);
    char *res, *res_p;
    char **q_strs = ALLOC_N(char *, snq->c_cnt);
    int len = 50;
    for (i = 0; i < snq->c_cnt; i++) {
        Query *clause = snq->clauses[i];
        q_strs[i] = clause->to_s(clause, field);
        len += strlen(q_strs[i]);
    }

    res_p = res = ALLOC_N(char, len);
    sprintf(res_p, "span_near[ ");
    res_p += strlen(res_p);
    for (i = 0; i < snq->c_cnt; i++) {
        sprintf(res_p, "%s, ", q_strs[i]);
        free(q_strs[i]);
        res_p += strlen(res_p);
    }
    free(q_strs);

    sprintf(res_p - 2, " ]");
    return res;
}
