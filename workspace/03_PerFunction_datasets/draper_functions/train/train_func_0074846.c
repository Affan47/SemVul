data(const QModelIndex &item, int role) const
{
    if (!item.isValid())
        return QVariant();

    const Internal::TreeItem *it = d->getItem(item);

    switch (role)
    {
    case Qt::EditRole :
    case Qt::DisplayRole :
        {
            return it->data(item.column());
        }
    case Qt::ToolTipRole :
        {
            return it->data(Constants::Data_Summary);
        }
    case Qt::ForegroundRole :
        {
            if (it->isTemplate()) {
                return QColor(settings()->value(Constants::S_FOREGROUND_TEMPLATES, "#000").toString());
            } else {
                return QColor(settings()->value(Constants::S_FOREGROUND_CATEGORIES, "darkblue").toString());
            }
        }
    case Qt::BackgroundRole :
        {
            QColor c;
            if (it->isTemplate()) {
                c = QColor(settings()->value(Constants::S_BACKGROUND_TEMPLATES, "white").toString());
            } else {
                c = QColor(settings()->value(Constants::S_BACKGROUND_CATEGORIES, "white").toString());
            }
            if (c.name()=="#ffffff")
                return QVariant();
            c.setAlpha(125);
            return c;
        }
    }
    return QVariant();
}
