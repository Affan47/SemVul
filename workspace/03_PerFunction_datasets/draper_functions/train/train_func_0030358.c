makeCacheKey(const QString &name, KIconLoader::Group group,
                                         const QStringList &overlays, int size, int state) const
{


    return (group == KIconLoader::User
                  ? QLatin1Literal("$kicou_")
                  : QLatin1Literal("$kico_"))
           % name
           % QLatin1Char('_')
           % QString::number(size)
           % QLatin1Char('_')
           % overlays.join("_")
           % ( group >= 0 ? mpEffect.fingerprint(group, state)
                          : *NULL_EFFECT_FINGERPRINT);
}
