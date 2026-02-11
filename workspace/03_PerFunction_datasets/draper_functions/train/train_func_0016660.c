spanne_next(SpanEnum *self)
{
    SpanNearEnum *sne = SpNEn(self);
    SpanEnum *se;

    se = sne->span_enums[sne->current];
    if (!se->next(se)) return false;

    return sne_next_match(self);
}
