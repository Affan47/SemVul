makeDateWidget()
{
  QWidget *e = new QDateEdit(d->m_item.value().toDate(), this);
  connect(e,    SIGNAL(valueChanged(QDate)),
          this, SLOT(slotDateChanged(QDate)));
  return e;
}
