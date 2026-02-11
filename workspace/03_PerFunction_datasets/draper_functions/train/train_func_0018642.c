saveToSettings(Core::ISettings *sets)
{
    Q_UNUSED(sets);

    Core::ISettings *s = sets? sets : settings();
    double x = 0.;
    double y = 0.;
    if (ui->horizCombo->currentIndex() == ToRight) {

        x += ui->horiz->value();
    } else {

        x -= ui->horiz->value();
    }
    if (ui->verticCombo->currentIndex() == ToTop) {

        y -= ui->vertic->value();
    } else {

        y += ui->vertic->value();
    }
    s->setValue(Core::Constants::S_PRINTERCORRECTION_HORIZ_MM, x);
    s->setValue(Core::Constants::S_PRINTERCORRECTION_VERTIC_MM, y);
    if (ui->direction->currentIndex() == 0)
        s->setValue(Core::Constants::S_PRINT_DIRECTION, Core::Constants::S_TOPTOBOTTOM);
    else
        s->setValue(Core::Constants::S_PRINT_DIRECTION, Core::Constants::S_BOTTOMTOTOP);
}
