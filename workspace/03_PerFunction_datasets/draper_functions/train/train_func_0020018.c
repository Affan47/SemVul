_parse_signature(const string &signature, string &type, unsigned int &i)
{
	for (; i < signature.length(); ++i)
	{
		switch (signature[i])
		{
			case 'a':
			{
				switch (signature[++i])
				{
					case '{':
					{
						type += "std::map< ";

						const char *atom = atomic_type_to_string(signature[++i]);
						if (!atom)
						{
							cerr << "invalid signature" << endl;
							exit(-1);
						}
						type += atom;
						type += ", ";
						++i;
						break;
					}
					default:
					{
						type += "std::vector< ";
						break;
					}
				}
				_parse_signature(signature, type, i);
				type += " >";
				continue;
			}
			case '(':
			{
				type += "::DBus::Struct< ";
				++i;
				_parse_signature(signature, type, i);
				type += " >";
				if (signature[i+1])
				{
					type += ", ";
				}
				continue;
			}
			case ')':
			case '}':
			{
				return;
			}
			default:
			{
				const char *atom = atomic_type_to_string(signature[i]);
				if (!atom)
				{
					cerr << "invalid signature" << endl;
					exit(-1);
				}
				type += atom;

				if (signature[i+1] != ')' && signature[i+1] != '}' && i+1 < signature.length())
				{
					type += ", ";
				}
				break;
			}
		}
	}
}
