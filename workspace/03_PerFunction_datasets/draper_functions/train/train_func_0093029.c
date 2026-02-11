read ( tnstream& stream )
{
   stream.readdata ( &id, sizeof ( id ));
   stream.readdata ( &name, sizeof ( name ));
   number = stream.readChar();
   color = stream.readChar();
   for ( int i = 0; i < 256; ++i ) {
      character[i].width = stream.readChar();
      character[i].size = stream.readWord();
      character[i].diskposition = stream.readInt();
      character[i].memposition = (char*) stream.readInt();
      character[i].dummy = stream.readChar();
   }
   height = stream.readWord();
   for ( int i = 0; i < 256; ++i )
      kernchartable[i] = stream.readChar();
   for ( int i = 0; i < 101; ++i )
      for ( int j = 0; j < 101; ++j )
         kerning[i][j] = stream.readChar();

   dummy = stream.readWord();
   useems = stream.readChar();
   caps = stream.readChar();
   palette = (dacpalette256*) stream.readInt();
   groundline = stream.readChar();
}
