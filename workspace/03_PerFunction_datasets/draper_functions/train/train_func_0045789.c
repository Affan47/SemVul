setDataToUi()
{
    double x = settings()->value(Core::Constants::S_PRINTERCORRECTION_HORIZ_MM, 0.).toDouble();
    double y = settings()->value(Core::Constants::S_PRINTERCORRECTION_VERTIC_MM, 0.).toDouble();
    if (x < 0.) {
        ui->horizCombo->setCurrentIndex(ToLeft);
    } else {
        ui->horizCombo->setCurrentIndex(ToRight);
    }
    if (y < 0.) {
        ui->verticCombo->setCurrentIndex(ToTop);
    } else {
        ui->verticCombo->setCurrentIndex(ToBottom);
    }
    ui->horizDist->setValue(50. + x);
    ui->verticDist->setValue(50. + y);

    if (settings()->value(Core::Constants::S_PRINT_DIRECTION) == Core::Constants::S_TOPTOBOTTOM)
        ui->direction->setCurrentIndex(0);
    else
        ui->direction->setCurrentIndex(1);
    shiftPreview();
}
