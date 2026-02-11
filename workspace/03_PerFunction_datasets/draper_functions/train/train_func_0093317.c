getbipath ( void )
{
   ASCString filename = getbi3path();
   appendbackslash( filename );
   filename += "mis";
   filename += pathdelimitterstring;
   filename += "*.dat";

   int cnt = 0;

   while ( !exist ( filename )) {
      filename = editString("enter Battle Isle path", filename );
      if ( filename.empty() )
         return "";

      appendbackslash(filename);

      CGameOptions::Instance()->BI3directory = filename;
      CGameOptions::Instance()->setChanged ( 1 );

      filename += "mis";
      filename += pathdelimitterstring;
      filename += "*.dat";

      cnt++;
      #if CASE_SENSITIVE_FILE_NAMES == 1
      if (!exist ( filename ) && cnt == 1 )
         displaymessage("The 'mis' and 'ger' / 'eng' directories must be lower case to import files from them !", 1 );
      #endif
   }

   return getbi3path();
}
