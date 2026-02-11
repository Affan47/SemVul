unparse_requirements(StringAccum &sa, const String &indent) const
{
    if (_requirements.size() > 0) {
	sa << indent << "require(";
	for (int i = 0; i < _requirements.size(); i++) {
	    if (i) sa << ", ";
	    sa << _requirements[i];
	}
	sa << ");\n\n";
    }
}
