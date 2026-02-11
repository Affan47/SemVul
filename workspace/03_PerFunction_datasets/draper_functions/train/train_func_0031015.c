pokemem_poke_activate( gpointer data, gpointer user_data )
{
  poke_t *poke = data;
  trainer_t *trainer = user_data;
  libspectrum_word bank = poke->bank;
  libspectrum_word address = poke->address;
  libspectrum_byte value;


  value = ( poke->value > 255 )? trainer->value : poke->value;

  if( bank == 8 ) {
    poke->restore = readbyte_internal( address );
    writebyte_internal( address, value );
  } else {
    address &= 0x3fff;
    poke->restore = RAM[ bank ][ address ];
    RAM[ bank ][ address ] = value;
  }
}
