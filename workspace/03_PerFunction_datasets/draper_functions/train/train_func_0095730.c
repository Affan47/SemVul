contextMenuEvent( QContextMenuEvent *event )
{
  QMenu *popup = createStandardContextMenu(event->pos());
  if (popup) {
    KIconTheme::assignIconsToContextMenu( isReadOnly() ? KIconTheme::ReadOnlyText
                                                       : KIconTheme::TextEditor,
                                          popup->actions() );

    popup->exec( event->globalPos() );
    delete popup;
  }
}
