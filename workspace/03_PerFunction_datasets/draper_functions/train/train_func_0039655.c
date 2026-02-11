load( const ASCString& filename )
{
   tnfilestream s ( filename, tnstream::reading );

   TextFormatParser tfp ( &s );
   auto_ptr<TextPropertyGroup> tpg ( tfp.run());

   PropertyReadingContainer pc ( "config", tpg.get() );

   runTextIO( pc );
}
