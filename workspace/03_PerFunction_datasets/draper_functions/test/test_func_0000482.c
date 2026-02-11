qrt_dump(struct routing_table *rt, bool full)
{
	struct sha1 digest;
	SHA1Context ctx;
	bool last_status = FALSE;
	int last_slot = 0;
	uint32 result;
	int i;

	g_debug("------ Query Routing Table \"%s\" "
		"(gen=%d, slots=%d, %scompacted)",
		rt->name, rt->generation, rt->slots, rt->compacted ? "" : "not ");

	SHA1Reset(&ctx);

	for (i = 0; i <= rt->slots; i++) {
		bool status = FALSE;
		uint8 value;

		if (i == rt->slots)
			goto final;

		status = qrt_dump_is_slot_present(rt, i);
		value = status ? 1 : 0;

		SHA1Input(&ctx, &value, sizeof value);

		if (i == 0) {
			last_slot = i;
			last_status = status;
			continue;
		}

		if (!last_status == !status)
			continue;

	final:
		if (full) {
			if (i - 1 != last_slot)
				g_debug("%d .. %d: %s", last_slot, i - 1,
					last_status ? "PRESENT" : "nothing");
			else
				g_debug("%d: %s", last_slot,
					last_status ? "PRESENT" : "nothing");

			last_slot = i;
			last_status = status;
		}
	}

	SHA1Result(&ctx, cast_to_pointer(&digest));


	result = sha1_hash(&digest);

	g_debug("------ End Routing Table \"%s\" "
		"(gen=%d, SHA1=%s, token=0x%x)",
		rt->name, rt->generation, sha1_base32(&digest), result);

	return result;
}
