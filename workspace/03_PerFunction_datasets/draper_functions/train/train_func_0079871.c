startElement(const QString &namespaceURI, const QString &localName,
                                    const QString &qName, const QXmlAttributes &attrs)
{
    Q_UNUSED(namespaceURI)
    Q_UNUSED(qName)


    int numAttrs = attrs.count();
    QString tag = localName.toLower();
    if (tag == "group") {
        QString group;
        for (int i = 0; i < numAttrs; ++i) {
            QString name = attrs.localName(i).toLower();
            if (name == "name") {

                group = attrs.value(i);
            }
        }
        if (group.isEmpty()) {
            group = d->baseGroup;
        } else {
            d->groups.append(group);
            if (!d->baseGroup.isEmpty()) {
                group = d->baseGroup + '\x1d' + group;
            }
        }
        m_config->setCurrentGroup(group);
    } else if (tag == "entry") {
        for (int i = 0; i < numAttrs; ++i) {
            QString name = attrs.localName(i).toLower();
            if (name == "name") {
                m_name = attrs.value(i).trimmed();
            } else if (name == "type") {
                m_type = attrs.value(i).toLower();
            } else if (name == "key") {
                m_key = attrs.value(i).trimmed();
            }
        }
    } else if (tag == "choice") {
        m_choice.name.clear();
        m_choice.label.clear();
        m_choice.whatsThis.clear();
        for (int i = 0; i < numAttrs; ++i) {
            QString name = attrs.localName(i).toLower();
            if (name == "name") {
                m_choice.name = attrs.value(i);
            }
        }
        m_inChoice = true;
    }

    return true;
}
