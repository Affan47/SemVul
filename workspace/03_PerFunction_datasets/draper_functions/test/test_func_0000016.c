spec_iter(const struct char_spec *spec)
{
    unsigned count;
    assert(spec->step);
    count = (1 + spec->end - spec->start)/spec->step;
    if (spec->negative)
	count *= 254;
    return count;
}
