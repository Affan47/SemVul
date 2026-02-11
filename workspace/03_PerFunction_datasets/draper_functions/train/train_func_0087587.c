print_htable(value_t v, ios_t *f)
{
    htable_t *h = (htable_t*)cv_data((cvalue_t*)ptr(v));
    size_t i;
    int first=1;
    fl_print_str("#table(", f);
    for(i=0; i < h->size; i+=2) {
        if (h->table[i+1] != HT_NOTFOUND) {
            if (!first) fl_print_str("  ", f);
            fl_print_child(f, (value_t)h->table[i]);
            fl_print_chr(' ', f);
            fl_print_child(f, (value_t)h->table[i+1]);
            first = 0;
        }
    }
    fl_print_chr(')', f);
}
