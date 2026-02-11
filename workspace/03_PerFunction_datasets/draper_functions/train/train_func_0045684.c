render(std::ostream &out) const {
	out << "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 ";

	switch(fType) {
		case eStrict: out << "Strict"; break;
		case eTransitional: out << "Transitional"; break;
		case eFrames: out << "Frameset"; break;
	}

	out << "//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-";

	switch(fType) {
		case eStrict: out << "strict"; break;
		case eTransitional: out << "transitional"; break;
		case eFrames: out << "frameset"; break;
	}

	out << ".dtd\">";
}
