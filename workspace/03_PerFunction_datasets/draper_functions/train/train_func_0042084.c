on_currentIndexChanged(int index)
{
    Q_EMIT currentCountryChanged(QLocale::Country(itemData(index).toInt()));
}
