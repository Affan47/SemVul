addTarget( ContainerBase* target )
{
   if ( find( targets.begin(), targets.end(), target ) == targets.end() )
      targets.push_back( target );
}
