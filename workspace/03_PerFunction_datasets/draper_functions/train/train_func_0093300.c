CreateNewRideFile(const RideFile *ride, int nRecStart, int nRecEnd)
{

    QDateTime newStart =  ride->startTime();
    RideFilePoint *pointStart = ride->dataPoints().at(nRecStart);
    newStart = newStart.addMSecs(static_cast<qint64>(pointStart->secs*1000 + 0.5));

    QString fileName;
    QString filePath;


    int offset = 0;
    QDateTime noConflicts;
    do {
        noConflicts = newStart.addSecs(offset);

        fileName.sprintf("%04d_%02d_%02d_%02d_%02d_%02d.gc",
                            noConflicts.date().year(), noConflicts.date().month(),
                            noConflicts.date().day(), noConflicts.time().hour(), noConflicts.time().minute(),
                            noConflicts.time().second());
        filePath = mainWindow->home.absolutePath() + "/" + fileName;

        offset++;

    } while (QFile(filePath).exists());
    newStart = newStart.addSecs(offset);


    QScopedPointer<RideFile> newRideFile(new RideFile(newStart, ride->recIntSecs()));
    for (int nItem = nRecStart; nItem<nRecEnd; ++nItem)
    {
        RideFilePoint *pPoint = ride->dataPoints().at(nItem);
        newRideFile->appendPoint(pPoint->secs-pointStart->secs, pPoint->cad, pPoint->hr, pPoint->km - pointStart->km,
                 pPoint->kph, pPoint->nm, pPoint->watts, pPoint->alt, pPoint->lon, pPoint->lat, pPoint->headwind, pPoint->slope,
                 pPoint->temp, pPoint->lrbalance, pPoint->interval-pointStart->interval);
    }
    newRideFile->setDeviceType(ride->deviceType());
    newRideFile->setFileFormat(ride->fileFormat());

    double endSecs = ride->dataPoints().at(nRecEnd - 1)->secs + ride->recIntSecs();
    foreach (RideFileInterval interval, ride->intervals()) {
        if ((interval.start >= pointStart->secs) && (interval.stop <= endSecs)) {
            newRideFile->addInterval(interval.start - pointStart->secs,
                                     interval.stop - pointStart->secs,
                                     interval.name);
        }
    }


    QFile file(filePath);
    if (file.exists())
    {
        QMessageBox::critical(this, tr("Split Ride"), tr("The file %1 already exists and will not be overwritten").arg(filePath));
        return;
    }


    GcFileReader f;
    f.writeRideFile(mainWindow, newRideFile.data(), file);


    mainWindow->addRide(fileName, false);
}
