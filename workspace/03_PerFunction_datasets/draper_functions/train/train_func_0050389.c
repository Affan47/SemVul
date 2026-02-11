savedata(QString data)
{
    int year = this->YearSelect->currentText().toInt();
    int month = this->monthCombo->currentText().toInt();
    int day = clickday;
    mycalendat->ctcl_savenote(year,month,day,data);
    note->hide();

}
