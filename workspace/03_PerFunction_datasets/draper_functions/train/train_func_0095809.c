saveSettings(QSettings *settings)
{
    qint64 lnb_lo = (qint64)(ui->lnbSpinBox->value()*1.e6);
    if (lnb_lo)
        settings->setValue("input/lnb_lo", lnb_lo);
    else
        settings->remove("input/lnb_lo");


    QMap <QString, QVariant> gains;
    getGains(&gains);
    if (gains.empty())
        settings->remove("input/gains");
    else
        settings->setValue("input/gains", gains);

    if (freqCorr())
        settings->setValue("input/corr_freq", freqCorr());
    else
        settings->remove("input/corr_freq");

    if (iqSwap())
        settings->setValue("input/swap_iq", true);
    else
        settings->remove("input/swap_iq");

    if (dcCancel())
        settings->setValue("input/dc_cancel", true);
    else
        settings->remove("input/dc_cancel");

    if (iqBalance())
        settings->setValue("input/iq_balance", true);
    else
        settings->remove("input/iq_balance");

    if (ignoreLimits())
        settings->setValue("input/ignore_limits", true);
    else
        settings->remove("input/ignore_limits");

    if (agc())
        settings->setValue("input/hwagc", true);
    else
        settings->remove("input/hwagc");


    if (ui->antSelector->count() > 1)
        settings->setValue("input/antenna", ui->antSelector->currentText());
    else
        settings->remove("input/antenna");
}
