spanne_destroy(SpanEnum *self)
{
    SpanEnum *se;
    SpanNearEnum *sne = SpNEn(self);
    int i;
    for (i = 0; i < sne->s_cnt; i++) {
        se = sne->span_enums[i];
        se->destroy(se);
    }
    free(sne->span_enums);
    free(self);
}
