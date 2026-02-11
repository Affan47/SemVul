writeText( ByteStream & str_out,
           const GUTF8String &textUTF8,
           const DjVuTXT::ZoneType zlayer,
           const GList<DjVuTXT::Zone> &children,
           const int WindowHeight )
{


  int layer=(int)zlayer;

  for(GPosition pos=children ; pos ; ++pos )
  {
    str_out.writestring(tolayer(layer,children[pos].ztype));
    writeText( str_out,
                textUTF8,
                children[pos],
                WindowHeight );
  }
  str_out.writestring(tolayer(layer,zlayer));
}
