header(const QString &separator = QString::null) const
    {

        return QString("%1 %2")
                .arg(interactingAtcLabels().join(";"))
                .arg(separator);
    }
