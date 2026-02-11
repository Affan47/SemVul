__extract_sorted_bios(struct thin_c *tc)
{
	struct rb_node *node;
	struct dm_thin_endio_hook *pbd;
	struct bio *bio;

	for (node = rb_first(&tc->sort_bio_list); node; node = rb_next(node)) {
		pbd = thin_pbd(node);
		bio = thin_bio(pbd);

		bio_list_add(&tc->deferred_bio_list, bio);
		rb_erase(&pbd->rb_node, &tc->sort_bio_list);
	}

	WARN_ON(!RB_EMPTY_ROOT(&tc->sort_bio_list));
}
