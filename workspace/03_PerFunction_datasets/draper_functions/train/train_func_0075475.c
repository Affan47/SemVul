forceCloseButtonHidden(bool hidden) {
  d->forceCloseButtonHidden=hidden;
  if (hidden) closeButton->hide();
  else closeButton->show();
}
