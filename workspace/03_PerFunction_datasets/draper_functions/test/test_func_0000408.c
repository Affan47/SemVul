write(const std::string &section, const std::string &name, double value, const int name_padding_width, const int value_padding_width, const std::string &comment )
{
	writeString(section, name, format(((std::abs(value)>1e-4 && std::abs(value)<1e4 ) || value==.0)? "%f" : "%e",value), name_padding_width,value_padding_width,comment);
}
