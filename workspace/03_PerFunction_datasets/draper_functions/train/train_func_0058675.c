RestoreOldPreferences( gpointer clocklist )
{
   extern GString *displayFormat;

   if ( ! g_string_equal( displayFormat, oldTimeDisplayFormat ) )
   {
       updateDisplayFormat( oldTimeDisplayFormat, clocklist );
   }
}
