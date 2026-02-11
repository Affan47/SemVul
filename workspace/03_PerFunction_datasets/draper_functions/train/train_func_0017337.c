setDatabase(DatabaseInfo* dbInfo)
{
    Database* db = dbInfo->database();
    ui->detailText->setText(tr("<html><i>No event chosen.</i></html>"));
    m_event.setDatabase(db);
    m_list.clear();
    if(db && db->index())
    {
        m_list = db->index()->tagValues(TagNameEvent);
    }
    m_list.sort();
    m_filterModel->setStringList(m_list);
    m_filterModel->sort(0);
}
