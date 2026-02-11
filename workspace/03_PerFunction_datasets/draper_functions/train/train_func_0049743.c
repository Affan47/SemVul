resize( int size )
{
   int oldsize  = states.size();
   states.resize(size);
   for ( int i = oldsize; i < size; ++i )
      states[i] = WAR;
}
