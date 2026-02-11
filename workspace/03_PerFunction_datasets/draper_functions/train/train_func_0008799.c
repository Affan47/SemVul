counterDataEquivalent(const StyleGeneratedData* otherStyle) const
{
    return compareCounterActList(counter_reset, otherStyle->counter_reset) &&
           compareCounterActList(counter_increment, otherStyle->counter_increment);
}
