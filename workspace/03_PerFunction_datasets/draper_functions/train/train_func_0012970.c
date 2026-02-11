tail_set_suffix (Tail *t, TrieIndex index, const TrieChar *suffix)
{
    index -= TAIL_START_BLOCKNO;
    if (index < t->num_tails) {


        TrieChar *tmp = NULL;
        if (suffix)
            tmp = (TrieChar *) strdup ((const char *)suffix);
        if (t->tails[index].suffix)
            free (t->tails[index].suffix);
        t->tails[index].suffix = tmp;

        return TRUE;
    }
    return FALSE;
}
