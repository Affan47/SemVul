set_loader_speed( libspectrum_byte *buffer, int speed,
		  libspectrum_byte border_colour )
{
  libspectrum_byte xor_colour;
  const turbo_variables_t *ptr;

  ptr = &turbo_variables[ speed ];

  buffer[ 94] = ptr->compare;
  buffer[118] = ptr->delay;


  xor_colour = ( border_colour == 0 ? 0x41 : 0x40 | border_colour );

  buffer[134] = xor_colour;
}
