selectLuaBrush()
{
   ASCString file = selectFile( "*.brush.lua", true );
   if ( file.empty () )
      return true;

   LuaBrush brush ( file );
   selection.setSelection( brush );


   return true;
}
