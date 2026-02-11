groupImpl(const QByteArray& aGroup) const
{
    Q_ASSERT_X(isValid(), "KConfigGroup::groupImpl", "accessing an invalid group");
    Q_ASSERT_X(!aGroup.isEmpty(), "KConfigGroup::groupImpl", "can not have an unnamed child group");

    KConfigGroup newGroup;

    newGroup.d = new KConfigGroupPrivate(const_cast<KConfigGroup*>(this), isGroupImmutableImpl(aGroup),
                                         true, aGroup);

    return newGroup;
}
