addPathInArg( const std::string &path,
                    const InArgs &in,
                    InArgs::const_iterator &itInArg,
                    PathArgument::Kind kind )
{
   if ( itInArg == in.end() )
   {

   }
   else if ( (*itInArg)->kind_ != kind )
   {

   }
   else
   {
      args_.push_back( **itInArg );
   }
}
