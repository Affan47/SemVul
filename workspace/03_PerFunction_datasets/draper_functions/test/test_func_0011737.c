forward( BidiMode useBidi )
{
  QString icon = ( useBidi == UseRTL && QApplication::isRightToLeft() )
                 ? "go-previous" : "go-next";
  return KGuiItem( i18nc( "go forward", "&Forward" ), icon,
                   i18n( "Go forward one step" ) );
}
