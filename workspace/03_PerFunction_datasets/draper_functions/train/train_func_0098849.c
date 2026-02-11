generalizable_or_pair(const Insn &x) const
{
    uint32_t value_diff = value.u ^ x.value.u;
    if (offset && x.offset == offset && mask.u && x.mask.u == mask.u
	&& (short_output || !x.short_output) && yes() == x.yes()
	&& (value_diff & (value_diff - 1)) == 0) {
	Insn test(offset, value.u & ~value_diff, mask.u & ~value_diff);
	return test.required_length() == required_length();
    } else
	return false;
}
