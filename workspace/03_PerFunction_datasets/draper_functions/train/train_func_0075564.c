rename( const ASCString& widgetName, const ASCString& newname, PG_Widget* parent )
{
   if ( !parent )
      parent = this;

   PG_Widget* w = parent->FindChild( widgetName, true );
   if ( w )
      w->SetName( newname );
}
