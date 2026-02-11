keyPressEvent( QKeyEvent *event )
{
    Q_D(KDialog);
  if ( event->modifiers() == 0 ) {
    if ( event->key() == Qt::Key_F1 ) {
      KPushButton *button = this->button( Help );

      if ( button ) {
        button->animateClick();
        event->accept();
        return;
      }
    }

    if ( event->key() == Qt::Key_Escape ) {
      KPushButton *button = this->button( d->mEscapeButton );

      if ( button ) {
        button->animateClick();
        event->accept();
        return;
      }

    }
  } else if ( event->key() == Qt::Key_F1 && event->modifiers() == Qt::ShiftModifier ) {
    QWhatsThis::enterWhatsThisMode();
    event->accept();
    return;
  } else if ( event->modifiers() == Qt::ControlModifier &&
            ( event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter ) ) {

    KPushButton *button = this->button( Ok );

    if ( button ) {
      button->animateClick();
      event->accept();
      return;
    }
  }

  QDialog::keyPressEvent( event );
}
