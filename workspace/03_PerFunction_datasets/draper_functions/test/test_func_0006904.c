markButtonPushed()
{
   mainWin->waitEnter();
   QList<QTreeWidgetItem *> treeItemList = fileWidget->selectedItems();
   QTreeWidgetItem *item;
   char cmd[1000];
   int count = 0;
   statusLine->setText("");
   foreach (item, treeItemList) {
      count++;
      bsnprintf(cmd, sizeof(cmd), "mark \"%s\"", item->text(1).toUtf8().data());
      item->setIcon(0, QIcon(QString::fromUtf8(":images/check.png")));
      m_console->write_dir(m_conn, cmd, false);
      if (m_console->read(m_conn) > 0) {
         strip_trailing_junk(m_console->msg(m_conn));
         statusLine->setText(m_console->msg(m_conn));
      }
      Dmsg1(dbglvl, "cmd=%s\n", cmd);
      m_console->discardToPrompt(m_conn);
   }
   if (count == 0) {
      mainWin->set_status("Nothing selected, nothing done");
      statusLine->setText("Nothing selected, nothing done");
   }
   mainWin->waitExit();
}
