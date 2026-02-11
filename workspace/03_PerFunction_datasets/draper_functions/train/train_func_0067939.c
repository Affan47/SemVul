fromXml(const QDomElement &xml)
{

    QList<GenericUpdateInformation> toReturn;
    if (!xml.isNull() && xml.tagName().compare(::TAG_SPEC_UPDATEINFO, Qt::CaseInsensitive)==0) {
        QDomElement update = xml.firstChildElement(::TAG_SPEC_UPDATEINFOVERSION);
        while (!update.isNull()) {
            QDomElement updateText = update.firstChildElement(::TAG_SPEC_UPDATEINFOVERSIONTEXT);
            GenericUpdateInformation updateItem;
            updateItem.setFromVersion(update.attribute(::ATTRIB_UPDATEINFOVERSION_FROM));
            updateItem.setToVersion(update.attribute(::ATTRIB_UPDATEINFOVERSION_TO));
            updateItem.setIsoDate(update.attribute(::ATTRIB_UPDATEINFOVERSION_DATE));
            while (!updateText.isNull()) {
                updateItem.setText(updateText.text(), updateText.attribute(::ATTRIB_LANGUAGE, Trans::Constants::ALL_LANGUAGE));
                updateText = updateText.nextSiblingElement(::TAG_SPEC_UPDATEINFOVERSIONTEXT);
            }
            toReturn << updateItem;
            update = update.nextSiblingElement(::TAG_SPEC_UPDATEINFOVERSION);
        }
    }
    return toReturn;
}
