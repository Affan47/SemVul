slotShowMenuBar()
{
    if (!m_showMenuBar->isChecked())
    {

        if (KMessageBox::warningContinueCancel(this,
            i18n("You have chosen to hide the menu bar.\n\nPlease remember that you can always use the shortcut \"%1\" to bring it back.", m_showMenuBar->shortcut().toString() ),
            i18n("Hide Menu"), KStandardGuiItem::cont(), KStandardGuiItem::cancel(), "showMenubar") != KMessageBox::Continue)
        {

            m_showMenuBar->setChecked(true);
            return;
        }
    }
    menuBar()->setVisible(m_showMenuBar->isChecked());
}
