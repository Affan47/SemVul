boosted_term_less_than(const BoostedTerm *bt1,
                                  const BoostedTerm *bt2)
{
    if (bt1->boost == bt2->boost) {
        return (strcmp(bt1->term, bt2->term) < 0);
    }

    return (bt1->boost < bt2->boost);
}
