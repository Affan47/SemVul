choices() const
{
    QList<KCoreConfigSkeleton::ItemEnum::Choice> r;
    foreach (const KCoreConfigSkeleton::ItemEnum::Choice2 &c, mChoices) {
        KCoreConfigSkeleton::ItemEnum::Choice cc = { c.name, c.label, c.whatsThis };
        r.append(cc);
    }
    return r;
}
