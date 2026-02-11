spanoq_eq(Query *self, Query *o)
{
    int i;
    Query *q1, *q2;
    SpanOrQuery *soq1 = SpOQ(self);
    SpanOrQuery *soq2 = SpOQ(o);

    if (!spanq_eq(self, o) || soq1->c_cnt != soq2->c_cnt) {
        return false;
    }
    for (i = 0; i < soq1->c_cnt; i++) {
        q1 = soq1->clauses[i];
        q2 = soq2->clauses[i];
        if (!q1->eq(q1, q2)) {
            return false;
        }
    }
    return true;
}
