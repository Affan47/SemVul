h2b(const BookEntry& h, bool swap_byteorder)
{
	if (!swap_byteorder) {
		return h;
	} else {
		BookEntry b;
		b.hashkey = reverse_byte_order(h.hashkey);
		for (unsigned int i=0; i<NR_MOVES; i++) {
#ifdef HOICHESS
			b.move[i] = Move(reverse_byte_order(h.move[i]));
#endif
			b.count[i] = reverse_byte_order(h.count[i]);
		}
		return b;
	}
}
