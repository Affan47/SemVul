sne_goto_next_doc(SpanNearEnum *sne)
{
    SpanEnum *se = sne->span_enums[sne->current];
    int prev_doc = se->doc(se);

    SpNEn_NEXT();

    while (se->doc(se) < prev_doc) {
        if (! se->skip_to(se, prev_doc)) {
            return false;
        }
        prev_doc = se->doc(se);
        SpNEn_NEXT();
    }
    return true;
}
