populateValues(Form::FormItem *item, const QDomElement &root, const XmlFormName &form)
{
    Q_UNUSED(form);
    QDomElement element = root.firstChildElement();
    while (!element.isNull()) {
        const QString &lang = element.attribute(Constants::ATTRIB_LANGUAGE, Trans::Constants::ALL_LANGUAGE);

        int id = element.attribute(Constants::ATTRIB_ID, 0).toInt();
        const QString &val = element.text();
        int type = m_ValuesTypes.value(element.tagName(), -1);
        if (type==Form::FormItemValues::Value_Printing) {


                item->valueReferences()->setValue(type, id, val, lang);

        } else if (type != -1) {
            item->valueReferences()->setValue(type, id, val, lang);
        }
        element = element.nextSiblingElement();
    }
    return true;
}
