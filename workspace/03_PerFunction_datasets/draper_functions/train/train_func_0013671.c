changeColors(const QStyleOptionViewItemV4 &optionV4, QString text)
    {
        if (optionV4.state & QStyle::State_Selected) {
            text.replace(QRegExp("color\\s*:\\s*gray", Qt::CaseInsensitive), "color:lightgray");
            text.replace(QRegExp("color\\s*:\\s*black", Qt::CaseInsensitive), "color:white");
            text.replace(QRegExp("color\\s*:\\s*blue", Qt::CaseInsensitive), "color:lightcyan");
            text.replace(QRegExp("color\\s*:\\s*red", Qt::CaseInsensitive), "color:bisque");
            text.replace(QRegExp("color\\s*:\\s*marron", Qt::CaseInsensitive), "color:#F2E6E6");
        }
        return text;
    }
