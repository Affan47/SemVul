unparse(bool force_binary)
{
    bool use_hexstring = force_binary;
    if (! use_hexstring)
    {
	unsigned int nonprintable = 0;
	int consecutive_printable = 0;
	for (unsigned int i = 0; i < this->val.length(); ++i)
	{
	    char ch = this->val.at(i);


	    if ((ch == 0) || (! (is_ascii_printable(ch) ||
				 strchr("\n\r\t\b\f", ch))))
	    {
		++nonprintable;
		consecutive_printable = 0;
	    }
	    else
	    {
		if (++consecutive_printable > 5)
		{


		    nonprintable = 0;
		    break;
		}
	    }
	}


	if (5 * nonprintable > val.length())
	{
	    use_hexstring = true;
	}
    }
    std::string result;
    if (use_hexstring)
    {
	result += "<" + QUtil::hex_encode(this->val) + ">";
    }
    else
    {
	result += "(";
	for (unsigned int i = 0; i < this->val.length(); ++i)
	{
	    char ch = this->val.at(i);
	    switch (ch)
	    {
	      case '\n':
		result += "\\n";
		break;

	      case '\r':
		result += "\\r";
		break;

	      case '\t':
		result += "\\t";
		break;

	      case '\b':
		result += "\\b";
		break;

	      case '\f':
		result += "\\f";
		break;

	      case '(':
		result += "\\(";
		break;

	      case ')':
		result += "\\)";
		break;

	      case '\\':
		result += "\\\\";
		break;

	      default:
		if (is_iso_latin1_printable(ch))
		{
		    result += this->val.at(i);
		}
		else
		{
		    result += "\\" + QUtil::int_to_string_base(
                        static_cast<int>(static_cast<unsigned char>(ch)),
                        8, 3);
		}
		break;
	    }
	}
	result += ")";
    }

    return result;
}
