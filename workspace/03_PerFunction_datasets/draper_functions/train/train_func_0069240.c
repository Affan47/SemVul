find_anagrams(struct wordlist *words, struct wordlist *stack,
              struct bitfield *bits, int maxwords, int length, int *maxtotal)
{
    struct bitfield *remaining_bits = NULL;
    struct wordlist *w = words;

    if (maxwords <= 0)
        return;

    if (*maxtotal <= 0)
        return;


    while (w != NULL) {
        if (length >= w->word->length) {
            if (bf_contains(bits, w->word->bits)) {
                int newlength = length - w->word->length;


                stack = push_wordstack(stack, w->word);
                if (newlength > 0) {
                    remaining_bits = bf_subtract(bits, w->word->bits);
                    find_anagrams(w, stack, remaining_bits,
                                  maxwords - 1, newlength, maxtotal);
                    free_bitfield(remaining_bits);
                } else {
                    if (*maxtotal > 0) {
                        print_wordstack(stack);
                        fputs("\n", stdout);
                        (*maxtotal)--;
                    }
                }
                stack = pop_wordstack(stack);
            }
        }
        w = w->next;
    }
}
