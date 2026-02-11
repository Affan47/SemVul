implies(const Insn &x, unsigned known_length) const
{
    if (!x.mask.u)
	return true;
    if (x.offset != offset || !implies_short_ok(true, x, true, known_length))
	return false;
    uint32_t both_mask = mask.u & x.mask.u;
    return both_mask == x.mask.u && (value.u & both_mask) == x.value.u;
}
