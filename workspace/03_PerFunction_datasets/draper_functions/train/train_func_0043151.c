filterExipired(QStringList &list)
{
   utime_t t, now = time(NULL);
   QString resultline, stat, LastWritten;
   QStringList fieldlist;


   if (m_chkExpired->isChecked()) {
      for (int i=list.size() -1; i >= 0; i--) {
         fieldlist = list.at(i).split("\t");
         ASSERT(fieldlist.size() != 9);
         LastWritten = fieldlist.at(7);
         if (LastWritten == "") {
            list.removeAt(i);

         } else {
            stat = fieldlist.at(8);
            t = str_to_utime(LastWritten.toAscii().data());
            t = t + stat.toULongLong();
            if (t > now) {
               list.removeAt(i);
            }
         }
      }
   }
}
