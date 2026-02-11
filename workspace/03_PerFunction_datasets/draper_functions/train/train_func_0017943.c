redo()
{
    if (m_firstTime) {
        m_sketchWidget->packItems(m_columns, m_ids, m_parentCommand, true);
        m_firstTime = false;
    }

    BaseCommand::redo();
}
