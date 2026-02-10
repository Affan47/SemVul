UpdateLookupTable(const QStringList &labels,
                                   const QStringList &candis,
                                   const QStringList &attrlists,
                                   bool has_prev, bool has_next)
{
    emit updateLookupTable(Args2LookupTable(labels, candis, attrlists, has_prev, has_next));
}
