GetTextImp( std::string* value ) const
{
	ValidatePointer();


	const char* retVal = m_tiXmlPointer->GetText();


	if ( 0 == retVal )
	{
		return false;
	}
	else
	{
		*value = retVal;
		return true;
	}
}
