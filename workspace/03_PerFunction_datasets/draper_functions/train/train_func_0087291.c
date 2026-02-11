data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.column() == EmptyColumn)
        return QVariant();

    if (index.row() >= d->m_Pmh->episodes().count())
        return QVariant();

    PmhEpisodeData *ep = d->m_Pmh->episodes().at(index.row());

    switch (role)
    {
    case Qt::EditRole :
        {
            switch (index.column())
            {
            case DateStart: return ep->data(PmhEpisodeData::DateStart);
            case DateEnd: return ep->data(PmhEpisodeData::DateEnd);
            case Label: return ep->data(PmhEpisodeData::Label);
            case IcdCodeList: return ep->data(PmhEpisodeData::IcdCodeList);
            case IcdLabelStringList : return ep->data(PmhEpisodeData::IcdLabelStringList);
            case IcdXml: return ep->data(PmhEpisodeData::IcdXml);
            }
            break;
        }
    case Qt::DisplayRole :
        {
            switch (index.column())
            {
            case DateStart: return ep->data(PmhEpisodeData::DateStart).toDate();
            case DateEnd: return ep->data(PmhEpisodeData::DateEnd).toDate();
            case Label: return ep->data(PmhEpisodeData::Label);
            case IcdCodeList: return ep->data(PmhEpisodeData::IcdCodeList);
            case IcdLabelStringList : return ep->data(PmhEpisodeData::IcdLabelStringList);
            default : return QVariant();
            }
            break;
        }
    case Qt::ToolTipRole :
        {
            return ep->data(PmhEpisodeData::IcdLabelHtmlList);
        }
    }


    return QVariant();
}
