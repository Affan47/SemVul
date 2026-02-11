spanne_new(Query *query, IndexReader *ir)
{
    int i;
    Query *clause;
    SpanEnum *self          = (SpanEnum *)emalloc(sizeof(SpanNearEnum));
    SpanNearQuery *snq      = SpNQ(query);

    SpNEn(self)->first_time = true;
    SpNEn(self)->in_order   = snq->in_order;
    SpNEn(self)->slop       = snq->slop;
    SpNEn(self)->s_cnt      = snq->c_cnt;
    SpNEn(self)->span_enums = ALLOC_N(SpanEnum *, SpNEn(self)->s_cnt);

    for (i = 0; i < SpNEn(self)->s_cnt; i++) {
        clause = snq->clauses[i];
        SpNEn(self)->span_enums[i] = SpQ(clause)->get_spans(clause, ir);
    }
    SpNEn(self)->current    = 0;

    SpNEn(self)->doc        = -1;
    SpNEn(self)->start      = -1;
    SpNEn(self)->end        = -1;

    self->query             = query;
    self->next              = &spanne_next;
    self->skip_to           = &spanne_skip_to;
    self->doc               = &spanne_doc;
    self->start             = &spanne_start;
    self->end               = &spanne_end;
    self->destroy           = &spanne_destroy;
    self->to_s              = &spanne_to_s;

    return self;
}
