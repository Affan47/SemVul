move( const String& path )
{

  if ( has_parent() ) parent().del_child( *this );
  parent_ = find_path_ptr( path.notail() );
  if ( parent_ == NULL )
    Message::message( Message_fatal( "Container: No such path- "+path ) );
  parent_->add_child( *this );
  name_ = path.tail();
  update();
}
