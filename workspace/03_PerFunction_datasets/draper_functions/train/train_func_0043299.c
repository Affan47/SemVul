WriteFloatEntry( const Property& pProperty, const std::string& pTypeName)
{
	if(pProperty.exist) {
		mOutput << startstr << "<" << pTypeName << ">" << endstr;
		PushTag();
		mOutput << startstr << "<float sid=\"" << pTypeName << "\">" << pProperty.value << "</float>" << endstr;
		PopTag();
		mOutput << startstr << "</" << pTypeName << ">" << endstr;
	}
}
