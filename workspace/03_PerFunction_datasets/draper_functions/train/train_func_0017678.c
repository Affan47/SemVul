remove( int32_t pos_1, int32_t pos_2 )

{
  assert( pos_1 >= 0 && pos_2 >= pos_1 && pos_2 <= _length );


  int32_t new_length    = _length - (pos_2 - pos_1);
  int32_t new_nb_blocks = nb_blocks( new_length );
  char*   new_genome    = new char[new_nb_blocks * BLOCK_SIZE];


  memcpy( new_genome, _data, pos_1 * sizeof(char) );
  memcpy( &new_genome[pos_1], &_data[pos_2], (new_length - pos_1) * sizeof(char) );
  new_genome[new_length] = '\0';


  delete [] _data;
  _data = new_genome;


  _length     = new_length ;
  _nb_blocks  = new_nb_blocks;
}
