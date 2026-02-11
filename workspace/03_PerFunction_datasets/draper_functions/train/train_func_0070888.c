print
	(
	 ostream& out, bool shortformat
	)
	{
	switch ((Val_type) type)
		{
	case int_type:
		out << hex << setfill((char)0x30) << setw(4);
		out << (value.intval&0xffff);
		out << dec;
		break;
	case pointer_type:
		out << hex << setfill((char)0x30) << setw(8);
		out << (long)value.ptr;
		out << dec;
		break;
	case string_type:
		out << '"' << value.str << '"'; break;
	case array_type:
		{
		out << "[ ";
		int i;
		for (i = 0; value.array[i].type != end_of_array_type; i++) {
			if (!shortformat || i < 2) {
				if (i)
					out << ", ";

				value.array[i].print(out);
			}
		}
		if (shortformat && i > 2)
			out << ", ... (size " << i << ")";
		out << " ]";
		}
		break;
	default:
		break;
		}
	}
