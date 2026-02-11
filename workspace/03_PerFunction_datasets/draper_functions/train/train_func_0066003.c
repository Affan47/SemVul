tool_db_event(void *ctx, int vec)
{
	struct tool_ctx *tc = ctx;
	u64 db_bits, db_mask;

	db_mask = ntb_db_vector_mask(tc->ntb, vec);
	db_bits = ntb_db_read(tc->ntb);

	dev_dbg(&tc->ntb->dev, "doorbell vec %d mask %#llx bits %#llx\n",
		vec, db_mask, db_bits);
}
