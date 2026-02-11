get_info_from_selection(QStringList &fileids,
                                       QStringList &jobids,
                                       QStringList &dirids,
                                       QStringList &findexes)
{
   struct stat statp;
   int32_t LinkFI;
   for (int i=0; i < RestoreList->rowCount(); i++) {
      QTableWidgetItem *item = RestoreList->item(i, 1);
      QString data = item->data(Qt::UserRole).toString();
      QStringList lst = data.split("\t");
      if (lst.at(1) != "0") {
         fileids << lst.at(2);
         jobids << lst.at(3);
         decode_stat(lst.at(4).toLocal8Bit().data(),
                     &statp, sizeof(statp), &LinkFI);
         if (LinkFI) {
            findexes << lst.at(3) + "," + QString().setNum(LinkFI);
         }
      } else {
         dirids << lst.at(0);
         jobids << lst.at(3).split(",");
      }
   }
   fileids.removeDuplicates();
   jobids.removeDuplicates();
   dirids.removeDuplicates();
   findexes.removeDuplicates();
}
