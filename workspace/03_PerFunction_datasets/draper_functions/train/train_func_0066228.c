ParseField(const unsigned char *begin,
					      const unsigned char *end)
{

	const unsigned char *headend = begin + sizeof(CommandTableField);
	if( headend > end )
		return headend;

	const CommandTableField *field = (const CommandTableField *) begin;


	begin += COMMAND_FIELD_HEADER_SIZE + field->size;
	if( begin > end )
		return begin;

	if( !field->size )
		return begin;

	Command command;
	command.Code = field->code;
	command.Name.assign((const char *)field->name, field->size);
	Commands.push_back(command);
	return begin;
}
