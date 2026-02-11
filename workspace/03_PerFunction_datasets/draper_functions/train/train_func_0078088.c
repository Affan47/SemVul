test_fastforward()
{
	song_iterator_t *it;
	song_iterator_t *simple_it = (song_iterator_t *) &simple_iterator;
	song_iterator_t *ff_it;
	unsigned char data[4];
	int result;
	puts("[TEST] fast-forward iterator");

	it = setup_simple_iterator(42, NULL, 0);
	ff_it = it = new_fast_forward_iterator(it, 0);
	ASSERT_FFIT;
	ASSERT_NEXT(42);
	ASSERT_SIT;
	ASSERT_NEXT(SI_FINISHED);
	ASSERT_SIT;

	it = setup_simple_iterator(42, NULL, 0);
	ff_it = it = new_fast_forward_iterator(it, 1);
	ASSERT_FFIT;
	ASSERT_NEXT(41);

	ASSERT_NEXT(SI_FINISHED);
	ASSERT_SIT;

	it = setup_simple_iterator(42, NULL, 0);
	ff_it = it = new_fast_forward_iterator(it, 41);
	ASSERT_FFIT;
	ASSERT_NEXT(1);

	ASSERT_NEXT(SI_FINISHED);
	ASSERT_SIT;

	it = setup_simple_iterator(42, NULL, 0);
	ff_it = it = new_fast_forward_iterator(it, 42);
	ASSERT_NEXT(SI_FINISHED);


	it = setup_simple_iterator(42, NULL, 0);
	ff_it = it = new_fast_forward_iterator(it, 10000);
	ASSERT_NEXT(SI_FINISHED);


	it = setup_simple_iterator(42, "\003\004", 2);
	ff_it = it = new_fast_forward_iterator(it, 2);
	ASSERT_FFIT;
	ASSERT_NEXT(1);
	ASSERT_CUE(1);
	ASSERT_SIT;
	ASSERT_NEXT(4);
	ASSERT_CUE(2);
	ASSERT_SIT;
	ASSERT_NEXT(35);
	ASSERT_NEXT(SI_FINISHED);
	ASSERT_SIT;

	it = setup_simple_iterator(42, "\003\004", 2);
	ff_it = it = new_fast_forward_iterator(it, 5);
	ASSERT_FFIT;
	ASSERT_CUE(1);
	ASSERT_FFIT;
	ASSERT_NEXT(2);
	ASSERT_CUE(2);
	ASSERT_SIT;
	ASSERT_NEXT(35);
	ASSERT_NEXT(SI_FINISHED);
	ASSERT_SIT;

	it = setup_simple_iterator(42, "\003\004", 2);
	ff_it = it = new_fast_forward_iterator(it, 41);
	ASSERT_FFIT;
	ASSERT_CUE(1);
	ASSERT_FFIT;
	ASSERT_CUE(2);
	ASSERT_FFIT;
	ASSERT_NEXT(1);
	ASSERT_NEXT(SI_FINISHED);
	ASSERT_SIT;

	puts("[TEST] Test OK.");
}
