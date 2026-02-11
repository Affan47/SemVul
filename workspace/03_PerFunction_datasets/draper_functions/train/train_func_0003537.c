Write(const ReadWriteXML* xml_class, const std::string& name, const TreeValue* value)
	{
		os << "<" << name;
		const char* type_attribute = xml_class->TypeAttribute();
		if (type_attribute != NULL)
		{
			os << " type=\"" << type_attribute << "\"";
		}
		os << ">";
		xml_class->WriteValue(*this, value);
		os << "</" << name << ">";
	}
