set_message_level( const int& level )
{
  if      ( level < 1 )            message_level_ = 1;
  else if ( level > fatal_level_ ) message_level_ = fatal_level_;
  else                             message_level_ = level;
}
