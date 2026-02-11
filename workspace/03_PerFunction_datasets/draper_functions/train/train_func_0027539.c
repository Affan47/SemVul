triewalk_rebase(triewalk *tw, const void *t)
{
    ptrdiff_t diff = ((const unsigned char *)t - (const unsigned char *)(tw->t));
    int i;

    tw->t = t;

    for (i = 0; i < tw->nswitches; i++)
	tw->switches[i].sw = (const struct trie_switch *)
	    ((const unsigned char *)(tw->switches[i].sw) + diff);
}
