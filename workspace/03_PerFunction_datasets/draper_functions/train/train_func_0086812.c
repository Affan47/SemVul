ButtonSprite(bool pushButton, const QString &id, ThemeManager* theme, int no, QGraphicsScene* scene)
           :  Themeable(id, theme), PixmapSprite(no, scene)
{

  mButtonPressed = false;
  mHover         = false;
  mPushButton    = pushButton;

  mSignal = new SpriteNotify(this);

  setAcceptedMouseButtons(Qt::NoButton);
  setAcceptsHoverEvents(false);


  mText  = new QGraphicsTextItem(this, scene);
  mText->hide();


  if (theme) theme->updateTheme(this);
}
