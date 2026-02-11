print_raw(int data)
{
	int b1, b2;
	if (data == -1)
		return -1;


	if (data == 0x8080)
	  return -1;

	b1 = data & 0x7f;
	b2 = (data>>8) & 0x7f;

	if (!semirawdata) {
	  fprintf(stderr,"%c%c",b1,b2);
	  return 0;
	}


	if ( ( b1 >= 0x10 ) && ( b1 <= 0x1F ) ) {
	  if ( ( b2 >= 0x20 ) && ( b2 <= 0x7F ) )
	    fprintf(stderr,"[%02X-%02X]",b1,b2);
	  return 0;
	}


	if ( ( b1 >= 0x0 ) && ( b1 <= 0xF ) ) {
	  fprintf(stderr,"(%02x)%c",b1,b2);


	  return 0;
	}
	if ( ( b2 >= 0x0 ) && ( b2 <= 0xF ) ) {
	  fprintf(stderr,"%c{%02x}",b1,b2);


	  return 0;
	}


	fprintf(stderr,"%c%c",b1,b2);

	return 0;
}
