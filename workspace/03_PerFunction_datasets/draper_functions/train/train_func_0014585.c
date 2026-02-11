process_variable_update_packet( ubyte *data, header *hinfo)
{
	int offset = HEADER_LENGTH;
	char value[TOKEN_LENGTH];
	int variable_index;


	GET_INT(variable_index);
	GET_STRING(value);
	PACKET_SET_SIZE();


	if ( (variable_index >= 0) && (variable_index < sexp_variable_count()) )
	{
		strcpy_s(Sexp_variables[variable_index].text, value);
	}


	if (MULTIPLAYER_MASTER) {
		send_variable_update_packet(variable_index, Sexp_variables[variable_index].text);
	}
}
