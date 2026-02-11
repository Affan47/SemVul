autoUpdate()
{

    QDate lastCheck = App::settings->value("Fotowall/LastUpdateCheck").toDate();
    if (lastCheck.isNull()) {
        App::settings->setValue("Fotowall/LastUpdateCheck", QDate::currentDate());
        return;
    }


    if (lastCheck.daysTo(QDate::currentDate()) > 30)
        QTimer::singleShot(2000, this, SLOT(checkForUpdates()));
}
