_k_menuAboutToShow()
{
    m_popup->clear();
    QStringList list;
    QDBusInterface klipper("org.kde.klipper", "/klipper", "org.kde.klipper.klipper");
    if (klipper.isValid()) {
      QDBusReply<QStringList> reply = klipper.call("getClipboardHistoryMenu");
      if (reply.isValid())
        list = reply;
    }
    QString clipboardText = qApp->clipboard()->text(QClipboard::Clipboard);
    if (list.isEmpty())
        list << clipboardText;
    bool found = false;
    const QFontMetrics fm = m_popup->fontMetrics();
    foreach (const QString& string, list)
    {
      QString text = fm.elidedText(string.simplified(), Qt::ElideMiddle, fm.maxWidth() * 20);
      text.replace('&', "&&");
      QAction* action = m_popup->addAction(text);
      if (!found && string == clipboardText)
      {
        action->setChecked(true);
        found = true;
      }
    }
}
