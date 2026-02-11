exportMetrics()
{
    QString fileName = QFileDialog::getSaveFileName( this, tr("Export Metrics"), QDir::homePath(), tr("Comma Separated Variables (*.csv)"));
    if (fileName.length() == 0)
        return;
    metricDB->writeAsCSV(fileName);
}
