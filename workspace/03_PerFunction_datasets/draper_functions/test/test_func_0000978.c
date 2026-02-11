writePathEntry(const char *pKey, const QString & path, WriteConfigFlags pFlags)
{
    Q_ASSERT_X(isValid(), "KConfigGroup::writePathEntry", "accessing an invalid group");
    Q_ASSERT_X(!d->bConst, "KConfigGroup::writePathEntry", "writing to a read-only group");

    config()->d_func()->putData(d->fullName(), pKey, translatePath(path).toUtf8(), pFlags, true);
}
