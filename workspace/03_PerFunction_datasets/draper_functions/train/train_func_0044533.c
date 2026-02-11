setDataToUi()
{

    const Utils::DatabaseConnector &db = settings()->databaseConnector();
    ui->host->setText(db.host());
    ui->log->setText(db.clearLog());
    ui->pass->setText(db.clearPass());
    ui->port->setValue(db.port());
    if (db.host().isEmpty()) {
        ui->host->setText("localhost");
        testHost("localhost");
    }
    ui->port->setValue(3306);
}
