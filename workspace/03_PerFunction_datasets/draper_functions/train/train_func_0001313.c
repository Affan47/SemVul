last_chars(struct fa *fa) {
    bitset *bs = bitset_init(UCHAR_NUM);

    list_for_each(s, fa->initial) {
        for (int i=0; i < s->tused; i++) {
            if (s->trans[i].to->accept) {
                for (uint c = s->trans[i].min; c <= s->trans[i].max; c++)
                    bitset_set(bs, c);
            }
        }
    }
    return bs;
}
