extractHotkey( const std::string& s )
{
   if ( !PG_Application::GetHighlightingTag() )
      return 0;

   bool found = false;
   for ( unsigned int i = 0; i < s.length(); ++i ) {
      if ( found )
         return tolower(s[i]);

      if ( s[i] == PG_Application::GetHighlightingTag() )
         found = true;
   }
   return 0;
}
