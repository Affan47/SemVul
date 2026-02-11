operator<< (std::string& out, const TiXmlNode& base )
{
   std::ostringstream os_stream( std::ostringstream::out );
   base.StreamOut( &os_stream );

   out.append( os_stream.str() );
   return out;
}
