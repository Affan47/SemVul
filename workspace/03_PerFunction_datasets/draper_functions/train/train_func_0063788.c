defaultClicked()
{
    if (ranges->currentItem()) {

        int index = ranges->invisibleRootItem()->indexOfChild(ranges->currentItem());
        HrZoneRange current = zonePage->zones.getHrZoneRange(index);


        QFont font;
        font.setWeight(QFont::Normal);
        ranges->currentItem()->setFont(0, font);
        ranges->currentItem()->setFont(1, font);


        zonePage->zones.setScheme(zonePage->schemePage->getScheme());
        zonePage->zones.setHrZonesFromLT(index);


        defaultButton->hide();


        rangeSelectionChanged();
    }
}
