isEntryImmutable(const char* key) const
{
    Q_ASSERT_X(isValid(), "KConfigGroup::isEntryImmutable", "accessing an invalid group");

    return (isImmutable() ||
        !config()->d_func()->canWriteEntry(d->fullName(), key, config()->readDefaults()));
}
