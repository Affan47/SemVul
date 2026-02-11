fromDefault(double value) const
{
    if (d->complex) {
        return d->complex->fromDefault(value);
    } else {
        return value / d->multiplier;
    }
}
