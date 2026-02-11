okButtonPushed()
{
   if (!selectJobRadio->isChecked()) {
      if (!checkJobIdList()) {
         return;
      }
   }
   QString cmd;

   this->hide();


   cmd = QString("restore");
   cmd += " fileset=\"" + filesetCombo->currentText() + "\"";
   cmd += " client=\"" + clientCombo->currentText() + "\"";
   if (selectJobRadio->isChecked()) {
      if (poolCombo->currentText() != tr("Any") ){
         cmd += " pool=\"" + poolCombo->currentText() + "\"";
      }
      cmd += " storage=\"" + storageCombo->currentText() + "\"";
      if (recentCheckBox->checkState() == Qt::Checked) {
         cmd += " current";
      } else {
         QDateTime stamp = beforeDateTime->dateTime();
         QString before = stamp.toString(mainWin->m_dtformat);
         cmd += " before=\"" + before + "\"";
      }
   } else {
      cmd += " jobid=\"" + jobIdEdit->text() + "\"";
   }
   if (selectFilesRadio->isChecked()) {
      if (!selectJobIdsRadio->isChecked())
         cmd += " select";
   } else {
      cmd += " all done";
   }

   if (mainWin->m_commandDebug) {
      Pmsg1(000, "preRestore command \'%s\'\n", cmd.toUtf8().data());
   }


   m_console->write_dir(m_conn, cmd.toUtf8().data());


   if (selectFilesRadio->isChecked()) {
      setConsoleCurrent();
      closeStackPage();

      mainWin->waitEnter();
   } else {
      closeStackPage();
      mainWin->resetFocus();
   }
   m_console->notify(m_conn, true);
   if (mainWin->m_miscDebug) Pmsg0(000, "preRestore OK pressed\n");
}
