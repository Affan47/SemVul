getHosts(void) const
{
    QStringList list;

    for (int i = 0; i < ui->hostListWidget->count(); i++)
    {
        list << ui->hostListWidget->item(i)->text();
    }

    return list;
}
