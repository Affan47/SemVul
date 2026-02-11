writeFile(ostream & os, bool para) const
{
	if (space == Default) return;

	string cmd = para ? "\\paragraph_spacing " : "\\spacing ";

	if (getSpace() == Spacing::Other) {
		os << cmd << spacing_string[getSpace()]
		   << ' ' << getValueAsString() << "\n";
	} else {
		os << cmd << spacing_string[getSpace()] << "\n";
	}
}
