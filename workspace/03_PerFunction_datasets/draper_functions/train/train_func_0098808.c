updateCopyAction()
{
    if (!m_CurrentEditor)
        return;
    const bool hasCopyableText = m_CurrentEditor->textEdit()->textCursor().hasSelection();
    if (aCut)
        aCut->setEnabled(hasCopyableText);
    if (aCopy) {
        aCopy->setEnabled(hasCopyableText);
    }
}
