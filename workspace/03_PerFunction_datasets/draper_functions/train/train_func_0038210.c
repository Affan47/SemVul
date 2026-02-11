clear()
{
    Q_ASSERT(m_DrugsModel);
    if (!m_DrugsModel)
        return;
    m_DrugsModel->clearDrugsList();
    m_DrugsModel->setModified(false);
}
