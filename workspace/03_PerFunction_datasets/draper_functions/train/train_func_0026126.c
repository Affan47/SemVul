populateTerminated()
{
   QString command = QString(".status storage=\"" + m_storage + "\" terminated");
   if (mainWin->m_commandDebug)
      Pmsg1(000, "sending command : %s\n",command.toUtf8().data());
   QStringList results;
   QBrush blackBrush(Qt::black);

   terminatedTable->clear();
   QStringList headerlist = (QStringList()
      << tr("Job Id") << tr("Job Level") << tr("Job Files")
      << tr("Job Bytes") << tr("Job Status") << tr("Job Time")
      << tr("Job Name"));
   QStringList flaglist = (QStringList()
      << "R" << "L" << "R" << "R" << "LC"
      << "L" << "L");

   terminatedTable->setColumnCount(headerlist.size());
   terminatedTable->setHorizontalHeaderLabels(headerlist);

   if (m_console->dir_cmd(command, results)) {
      int row = 0;
      QTableWidgetItem* p_tableitem;
      terminatedTable->setRowCount(results.size());
      foreach (QString line, results) {

         QStringList fieldlist = line.split("\t");
         int column = 0;
         QString statusCode("");

         foreach (QString field, fieldlist) {
            field = field.trimmed();
            p_tableitem = new QTableWidgetItem(field, 1);
            p_tableitem->setForeground(blackBrush);
            p_tableitem->setFlags(0);
            if (flaglist[column].contains("R"))
               p_tableitem->setTextAlignment(Qt::AlignRight);
            if (flaglist[column].contains("C")) {
               if (field == "OK")
                  p_tableitem->setBackground(Qt::green);
               else
                  p_tableitem->setBackground(Qt::red);
            }
            terminatedTable->setItem(row, column, p_tableitem);
            column += 1;
         }
         row += 1;
      }
   }
   terminatedTable->resizeColumnsToContents();
   terminatedTable->resizeRowsToContents();
   terminatedTable->verticalHeader()->hide();
}
