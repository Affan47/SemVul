MainWindow( QWidget* parent, Qt::WindowFlags f )
    : KXmlGuiWindow( parent, f ), d(new MainWindowPrivate())
{
  PartBase::setPartObject( this );
}
