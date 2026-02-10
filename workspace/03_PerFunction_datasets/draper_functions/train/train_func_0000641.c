push(QUndoCommand * cmd)
{
#ifndef QT_NO_DEBUG
	writeUndo(cmd, 0, NULL);
#endif
    if (m_temporary == cmd) {
        m_temporary->redo();
        return;
    }

	QUndoStack::push(cmd);
}
