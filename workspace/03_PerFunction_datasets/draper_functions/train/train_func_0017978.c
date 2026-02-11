toString()
{
	std::stringstream stream;
	stream << "amSynth1.0preset" << std::endl;
	stream << "<preset> " << "<name> " << getName() << std::endl;
	for (unsigned n = 0; n < ParameterCount(); n++) {
		stream << "<parameter> " << getParameter(n).getName() << " " << getParameter(n).getValue() << std::endl;
	}
	return stream.str();
}
