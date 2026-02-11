selection() const
{
    QStringList selection;


    QTreeWidgetItemIterator it(const_cast<KTimeZoneWidget*>(this), d->itemsCheckable ? QTreeWidgetItemIterator::Checked : QTreeWidgetItemIterator::Selected);
    for (; *it; ++it) {
        selection.append( (*it)->data( Private::CityColumn, Private::ZoneRole ).toString() );
    }

    return selection;
}
