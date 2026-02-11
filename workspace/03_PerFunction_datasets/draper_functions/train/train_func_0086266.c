initialize_primary_key_from_commands (
	const XMLTree& tree, PatchPrimaryKey& id, const XMLNode* node)
{
	id.bank_number = 0;

	const XMLNodeList events = node->children();
	for (XMLNodeList::const_iterator i = events.begin(); i != events.end(); ++i) {

		XMLNode* node = *i;
		if (node->name() == "ControlChange") {
			const string& control = node->property("Control")->value();
			const string& value   = node->property("Value")->value();

			if (control == "0") {
				id.bank_number |= string_to_int(tree, value) << 7;
			} else if (control == "32") {
				id.bank_number |= string_to_int(tree, value);
			}

		} else if (node->name() == "ProgramChange") {
			const string& number = node->property("Number")->value();
			assert(number != "");
			id.program_number = string_to_int(tree, number);
		}
	}

	return 0;
}
