_k_chooseColor()
{
    KColorDialog *dialog = dialogPtr.data();
    if (dialog) {
        dialog->show();
        KWindowSystem::forceActiveWindow(dialog->winId());
        return;
    }

    dialog = new KColorDialog(q);
    dialog->setColor(q->color());
    if (m_bdefaultColor) {
        dialog->setDefaultColor(m_defaultColor);
    }
    dialog->setAlphaChannelEnabled(m_alphaChannel);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->setButtons(KDialog::Ok | KDialog::Cancel);
    connect(dialog, SIGNAL(applyClicked()), q, SLOT(_k_colorChosen()));
    connect(dialog, SIGNAL(accepted()), q, SLOT(_k_colorChosen()));
    dialogPtr = dialog;
    dialog->show();
}
