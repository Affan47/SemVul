totalComposers() const
{
    QStringList composers = query( "SELECT COUNT( id ) FROM composers;" );
    if( composers.size() < 1 )
        return 0;
    QString total = composers[0];
    return total.toInt();
}
