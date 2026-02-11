changeWeek(QAction *action)
{
    QDate monday = action->data().toDate();
    setViewType(View_Week);
    setDate(monday);
}
