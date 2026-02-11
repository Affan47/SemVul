render(std::ostream& out) const {
	out << "<?" << fName;
	if(getAttributes() != 0) {
		out << ' ';
		fAttributes->render(out);
	}
	out << "?>";
}
