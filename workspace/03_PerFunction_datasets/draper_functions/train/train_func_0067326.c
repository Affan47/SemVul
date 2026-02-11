saveSettings(QSettings *settings)
{
    int  intval;

    if (!settings)
        return;

    settings->beginGroup("fft");

    intval = fftSize();
    if (intval != DEFAULT_FFT_SIZE)
        settings->setValue("fft_size", intval);
    else
        settings->remove("fft_size");

    intval = fftRate();
    if (intval != DEFAULT_FFT_RATE)
        settings->setValue("fft_rate", fftRate());
    else
        settings->remove("fft_rate");

    if (ui->fftAvgSlider->value() != DEFAULT_FFT_AVG)
        settings->setValue("averaging", ui->fftAvgSlider->value());
    else
        settings->remove("averaging");

    if (ui->fftSplitSlider->value() != DEFAULT_FFT_SPLIT)
        settings->setValue("split", ui->fftSplitSlider->value());
    else
        settings->remove("split");

    QColor fftColor = ui->colorPicker->currentColor();
    if (fftColor != QColor(0xFF,0xFF,0xFF,0xFF))
        settings->setValue("pandapter_color", fftColor);
    else
        settings->remove("pandapter_color");

    if (ui->fillButton->isChecked())
        settings->setValue("pandapter_fill", true);
    else
        settings->remove("pandapter_fill");

    settings->endGroup();
}
