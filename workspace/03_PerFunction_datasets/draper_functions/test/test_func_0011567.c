createWidget( QWidget * _parent )
{
  QToolBar *parent = qobject_cast<QToolBar *>(_parent);
  if (!parent)
    return KAction::createWidget(_parent);
  QToolButton* button = new QToolButton(parent);
  button->setAutoRaise(true);
  button->setFocusPolicy(Qt::NoFocus);
  button->setIconSize(parent->iconSize());
  button->setToolButtonStyle(parent->toolButtonStyle());
  QObject::connect(parent, SIGNAL(iconSizeChanged(QSize)),
                   button, SLOT(setIconSize(QSize)));
  QObject::connect(parent, SIGNAL(toolButtonStyleChanged(Qt::ToolButtonStyle)),
                   button, SLOT(setToolButtonStyle(Qt::ToolButtonStyle)));
  button->setDefaultAction(this);
  QObject::connect(button, SIGNAL(triggered(QAction*)), parent, SIGNAL(actionTriggered(QAction*)));

  if (delayed())
    button->setPopupMode(QToolButton::DelayedPopup);
  else if (stickyMenu())
    button->setPopupMode(QToolButton::InstantPopup);
  else
    button->setPopupMode(QToolButton::MenuButtonPopup);

  return button;
}
