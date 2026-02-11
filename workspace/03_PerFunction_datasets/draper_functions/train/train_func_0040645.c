setFilterParam(int lo, int hi)
{
    float width_f = fabs((hi-lo)/1000.0);

    ui->filterCombo->setCurrentIndex(FILT_SEL_USER_IDX);
    ui->filterCombo->setItemText(FILT_SEL_USER_IDX, QString("User (%1k)").arg(width_f));

}
