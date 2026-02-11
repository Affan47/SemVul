operator>>(char const * required)
{
	string token;
	*this >> token;
	if (token != required) {
		LYXERR0("Missing '" << required << "'-tag in " << pimpl_->context
			<< ". Got " << token << " instead. Line: " << lineNumber());
		pushToken(token);
	}
	return *this;
}
