message_check(const struct message * const m, unsigned chunk_idx)
{
	g_assert(m != NULL);
	slot_check(m->slot, chunk_idx);
	g_assert(chunk_idx == m->chunk_idx);
}
