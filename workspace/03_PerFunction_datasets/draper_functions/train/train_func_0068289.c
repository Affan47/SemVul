headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        return GetHHeaderLabel(section);
    }
    else if (role == Qt::DecorationRole && orientation == Qt::Horizontal)
    {
        if (section == GetColIx(COL_DOUBLES))
        {
            return QVariant(QIcon(":/img/same_color_header.png"));
        }
    }
    else if (role == Qt::ToolTipRole && orientation == Qt::Horizontal)
    {
        if (section == GetColIx(COL_DOUBLES))
        {
            return QVariant(QString(tr("Pegs of Same Color")));
        }
        else if (section == GetColIx(COL_DELETE))
        {
            return QVariant(QString(tr("Actions")));
        }
        else if (section == GetColIx(COL_RANKING))
        {
            return QVariant(QString(tr("Rank")));
        }
    }
    return QVariant();
}
