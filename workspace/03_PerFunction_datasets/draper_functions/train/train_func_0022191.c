initUndoStack(const QString& undoStackId)
{
    if (m_undoStacks->contains(undoStackId))
    {
        m_currentUndoStack = m_undoStacks->value(undoStackId);
    }
    else
    {
        m_currentUndoStack = new QUndoStack(this);
        m_undoStacks->insert(undoStackId, m_currentUndoStack);
        undoGroup()->addStack(m_currentUndoStack);
    }

    undoGroup()->setActiveStack(m_currentUndoStack);
}
