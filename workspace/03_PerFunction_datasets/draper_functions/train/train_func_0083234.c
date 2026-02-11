toTimeSpec(const Spec &spec) const
{
    if (spec == d->spec())
        return *this;
    if (!isValid())
        return KDateTime();
    if (d->dateOnly())
        return KDateTime(d->date(), spec);
    if (spec.type() == TimeZone)
    {
        KDateTime result;
        d->newToZone(result.d, spec.timeZone());
        return result;
    }
    return KDateTime(d->toUtc(), spec);
}
