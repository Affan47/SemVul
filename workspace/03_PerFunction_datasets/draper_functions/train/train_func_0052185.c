check_threshold(struct threshold *t, dm_block_t value)
{
	if (below_threshold(t, value) &&
	    !threshold_already_triggered(t))
		t->fn(t->context);

	t->value_set = true;
	t->current_value = value;
}
