sizeHint() const
{
    if ( QToolBar *toolBar = qobject_cast<QToolBar*>( parentWidget() ) )
        return toolBar->iconSize();

    return QDial::sizeHint();
}
