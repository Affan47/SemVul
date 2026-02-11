SaveParameter()
{
   ASCString filename = selectFile( fileNamePattern, false );
   if ( !filename.empty() ) {
      tn_file_buf_stream s ( filename, tnstream::writing );
      PropertyWritingContainer pc ( blockName, s );
      runTextIO( pc );
      return true;
   }
   return false;
}
