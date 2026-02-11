stringToStereoOption(char* v)
{
	std::string o = v;
	for (unsigned int i = 0; i < o.length(); i++) o[i] = toupper(o[i]);
	if (!o.compare("NO"))     return OpenBabel::OBSpectrophore::NoStereoSpecificProbes;
	if (!o.compare("UNIQUE")) return OpenBabel::OBSpectrophore::UniqueStereoSpecificProbes;
	if (!o.compare("MIRROR")) return OpenBabel::OBSpectrophore::MirrorStereoSpecificProbes;
	if (!o.compare("ALL"))    return OpenBabel::OBSpectrophore::AllStereoSpecificProbes;
	return OpenBabel::OBSpectrophore::NoStereoSpecificProbes;
}
