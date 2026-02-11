KEditToolBarWidget( QWidget *parent )
  : QWidget(parent),
    d(new KEditToolBarWidgetPrivate(this, componentData(), KXMLGUIClient::actionCollection() ))
{
    d->setupLayout();
}
