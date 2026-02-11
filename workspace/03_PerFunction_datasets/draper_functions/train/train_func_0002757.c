ReadValue(XMLReadingMachine& , const pugi::xml_node& element) const
	{

		const char* text = "";
		for (pugi::xml_node child = element.first_child(); child; child = child.next_sibling())
		{
			if (child.type() == pugi::node_pcdata)
			{
				text = child.value();
				break;
			}
		}


		int textlength = strlen(text);


		std::vector<UInt8> decoded_binary(textlength);


		base64_decodestate state;
		base64_init_decodestate(&state);
		int decoded_length = base64_decode_block(text, textlength, (char*) &decoded_binary[0], &state);


		MemoryHandlerBasic binary_handler((size_t)decoded_length);
		memcpy(binary_handler.Data(), &decoded_binary[0], (size_t)decoded_length);


		return new TreeBinary(&binary_handler);
	}
