LineEndTypesSupported() {
	if (instance) {
		int interfaceVersion = instance->Version();
		if (interfaceVersion >= lvSubStyles) {
			ILexerWithSubStyles *ssinstance = static_cast<ILexerWithSubStyles *>(instance);
			return ssinstance->LineEndTypesSupported();
		}
	}
	return 0;
}
