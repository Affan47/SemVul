slotAction(QAction* action)
{
    if(m_actions.contains(action))
    {
        EditAction editAction = m_actions[action];
        editAction.setMove(m_currentMove);
        emit actionRequested(editAction);
    }
}
