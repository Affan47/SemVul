getAvailabilities() const
{
    QList<DayAvailability> toReturn;
    int day = ui->dayCombo->currentIndex()+1;
    if (day != -1 && day <= Qt::Sunday) {

        DayAvailability av;
        av.setWeekDay(day);
        av.addTimeRange(ui->startTime->time(), ui->endTime->time());
        toReturn << av;
    } else if (day == Qt::Sunday+1) {

        for(int i = Qt::Monday; i <= Qt::Friday ; ++i) {
            DayAvailability av;
            av.setWeekDay(i);
            av.addTimeRange(ui->startTime->time(), ui->endTime->time());
            toReturn << av;
        }
    }
    return toReturn;
}
