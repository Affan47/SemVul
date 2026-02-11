has_guess_block_as_last_item( Junction *q )
#else
has_guess_block_as_last_item( q )
Junction *q;
#endif
{
	Junction *alt;

    if (q == NULL) return 0;
	for (alt=q; alt->p2 != NULL && !( (Junction *) alt->p2)->ignore; alt= (Junction *) alt->p2 ) {};
    return first_item_is_guess_block( (Junction *) alt->p1) != NULL;
}
