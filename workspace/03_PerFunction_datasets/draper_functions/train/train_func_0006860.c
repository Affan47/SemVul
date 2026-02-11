parse_uint8(private_parser_t *this, int rule_number,
						u_int8_t *output_pos)
{
	if (this->byte_pos + sizeof(u_int8_t) > this->input_roof)
	{
		return short_input(this, rule_number);
	}
	if (this->bit_pos)
	{
		return bad_bitpos(this, rule_number);
	}
	if (output_pos)
	{
		*output_pos = *(this->byte_pos);
		DBG3(DBG_ENC, "   => %hhu", *output_pos);
	}
	this->byte_pos++;
	return TRUE;
}
