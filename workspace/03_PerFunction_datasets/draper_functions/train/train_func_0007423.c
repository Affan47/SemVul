setAntenna(const QString &antenna)
{
    int index = ui->antSelector->findText(antenna, Qt::MatchExactly);
    if (index != -1)
        ui->antSelector->setCurrentIndex(index);
}
