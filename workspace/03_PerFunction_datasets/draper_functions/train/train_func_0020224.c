buildTestsToRun(QStandardItem *item,
                              QString baseIndex,
                              QVariantMap &items) {
    if (item->checkState() == Qt::Checked || item->checkState() == Qt::PartiallyChecked) {
        if (item->hasChildren()) {
            myQMap testMap;
            testMap[item->text()] = "menu";
            items[baseIndex] = QVariant::fromValue<QMap<QString,QString> >(testMap);
            int internalIndex = 1;
            for (int i = 0; i< item->rowCount(); i++) {
                QStandardItem *childItem = item->child(i);
                buildTestsToRun(childItem, baseIndex + "."+QString::number(internalIndex), items);
                if(childItem->checkState() == Qt::Checked || childItem->checkState() == Qt::PartiallyChecked)
                    internalIndex++;
            }
        } else {
            myQMap testMap;
            testMap[item->text()] = item->data(Qt::UserRole).toString();
            items[baseIndex] = QVariant::fromValue<QMap<QString,QString> > (testMap);
        }
    }
}
