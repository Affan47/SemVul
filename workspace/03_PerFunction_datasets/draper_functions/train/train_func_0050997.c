releaseDialog(PlannedDialog *dialog)
{
    if (dialog == m_activeDialog) {
        m_activeDialog = NULL;
    }
    dialog->killTalk();
    delete dialog;
}
