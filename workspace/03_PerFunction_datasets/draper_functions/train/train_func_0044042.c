charactersPerMinuteData(int row, int role) const
{
    int charactersPerMinute = this->charactersPerMinute(row);

    switch(role)
    {
    case Qt::DisplayRole:
        return QVariant(charactersPerMinute);
    default:
        return QVariant();
    }
}
