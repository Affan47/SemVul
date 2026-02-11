layout() {

  const QSize bs = bestButtonSize();

  foreach(Item *item, data->buttons) {
    QPushButton* const b = item->button;
    if(b) {
      if(item->noexpand)
	b->setFixedSize(buttonSizeHint(b));
      else
	b->setFixedSize(bs);
    }
  }

  setMinimumSize(sizeHint());
}
