allInStatus(Qt::CheckState wanted_status)
{
    for (int i=0; i< rowCount(); i++) {
        QStandardItem *item = this->item(i, 0);
        if (!item)
            continue;
        if (item->checkState() != wanted_status) {
            return false;
        }
    }
    return true;
}
