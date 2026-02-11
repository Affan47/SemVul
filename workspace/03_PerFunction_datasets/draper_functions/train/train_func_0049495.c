emit_byte(u8 data)
{
	if ( opc == olen)
	{
	    increase_output_buffer();
	}


	*(ostart+opc) = data ;
	opc++;
}
