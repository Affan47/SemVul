segment_cmp (Segment *s1,
	     Segment *s2)
{
	if (s1->start_at < s2->start_at)
		return -1;
	else if (s1->start_at > s2->start_at)
		return 1;

	g_assert (s1->start_at == s1->end_at || s2->start_at == s2->end_at);
#ifdef ENABLE_DEBUG


	g_assert_not_reached ();
#endif
	g_return_val_if_reached (s1->end_at < s2->end_at ? -1 :
                                 (s1->end_at > s2->end_at ? 1 : 0));
}
