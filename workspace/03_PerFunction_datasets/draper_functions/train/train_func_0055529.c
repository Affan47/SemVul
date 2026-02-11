printRange(ostream& out) const {
	out << "min = ";
	if (isMinValid()) out << m_Min; else out << "?";
	out << " max = ";
	if (isMaxValid()) out << m_Max; else out << "?";
	return out;
}
