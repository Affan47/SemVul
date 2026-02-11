put(std::ostream &out) const {
	if (this->filename != NULL) {
		out << *this->filename << ":" << this->line;
	} else {
		out << "BUILTIN [" << this->information << "]";
	}
	return out;
}
