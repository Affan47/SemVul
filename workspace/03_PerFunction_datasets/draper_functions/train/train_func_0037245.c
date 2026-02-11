setRelativeValue(double r)
{
    if (!d->referencePoint) {
        return;
    }
    ++d->blockRelative;
    setValue(r * d->referencePoint);
    --d->blockRelative;
}
