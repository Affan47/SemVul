lastValue(uint i) const
{
    if (d->plotData.isEmpty() || d->plotData.first().size() <= (int)i) {
        return 0;
    }
    return d->plotData.first()[i];
}
