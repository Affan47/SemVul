initObject(const QDate & date)
{
  setValidator(0);
  popupFrame = new KPopupFrame(this);
  popupFrame->installEventFilter(this);
  datePicker = new KDatePicker(date, popupFrame);
  datePicker->setMinimumSize(datePicker->sizeHint());
  datePicker->installEventFilter(this);
  popupFrame->setMainWidget(datePicker);
  setDate(date);

  connect(datePicker, SIGNAL(dateSelected(QDate)), this, SLOT(dateEnteredEvent(QDate)));
  connect(datePicker, SIGNAL(dateEntered(QDate)), this, SLOT(dateEnteredEvent(QDate)));
}
