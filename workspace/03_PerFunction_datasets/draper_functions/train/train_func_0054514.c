priorityFromXml(const QString &xml)
    {

        _priority = AlertItem::Low;
        if (xml.compare("high", Qt::CaseInsensitive)==0) {
            _priority = AlertItem::High;
        } else if (xml.compare("medium", Qt::CaseInsensitive)==0) {
            _priority = AlertItem::Medium;
        }
    }
