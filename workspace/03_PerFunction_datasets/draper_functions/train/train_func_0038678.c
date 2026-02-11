refreshClicked()
{
    progressLabel->setText(tr("Downloading ride list..."));
    progressBar->setMinimum(0);
    progressBar->setMaximum(1);
    progressBar->setValue(0);


    foreach (QTreeWidgetItem *curr, rideList->invisibleRootItem()->takeChildren()) {
        QCheckBox *check = (QCheckBox*)rideList->itemWidget(curr, 0);
        QCheckBox *exists = (QCheckBox*)rideList->itemWidget(curr, 6);
        delete check;
        delete exists;
        delete curr;
    }
    foreach (QTreeWidgetItem *curr, rideListUp->invisibleRootItem()->takeChildren()) {
        QCheckBox *check = (QCheckBox*)rideListUp->itemWidget(curr, 0);
        QCheckBox *exists = (QCheckBox*)rideListUp->itemWidget(curr, 6);
        delete check;
        delete exists;
        delete curr;
    }
    foreach (QTreeWidgetItem *curr, rideListSync->invisibleRootItem()->takeChildren()) {
        QCheckBox *check = (QCheckBox*)rideListSync->itemWidget(curr, 0);
        delete check;
        delete curr;
    }


    rideMetrics = main->metricDB->getAllMetricsFor(QDateTime(from->date()), QDateTime(to->date()));


    workouter->list(
                  athleteCombo->itemData(athleteCombo->currentIndex()).toInt(),
                  from->date(),
                  to->date(),
                  appsettings->cvalue(main->cyclist, GC_TPUSER, "null").toString(),
                  appsettings->cvalue(main->cyclist, GC_TPPASS, "null").toString());


    rideFiles.clear();
    QStringListIterator i(RideFileFactory::instance().listRideFiles(main->home));
    for (i.toFront(); i.hasNext();) rideFiles << QFileInfo(i.next()).baseName().mid(0,14);

}
