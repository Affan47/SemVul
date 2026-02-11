updateRedoAction()
{
    if (aRedo)
        aRedo->setEnabled(m_CurrentEditor && m_CurrentEditor->textEdit()->document()->isRedoAvailable());
}
