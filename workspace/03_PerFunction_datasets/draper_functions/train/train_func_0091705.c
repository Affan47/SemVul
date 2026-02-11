ReadLightLibrary()
{
	if( mReader->isEmptyElement())
		return;

	while( mReader->read())
	{
		if( mReader->getNodeType() == irr::io::EXN_ELEMENT) {
			if( IsElement( "light"))
			{

				int attrID = GetAttribute( "id");
				std::string id = mReader->getAttributeValue( attrID);


				ReadLight(mLightLibrary[id] = Light());

			} else
			{

				SkipElement();
			}
		}
		else if( mReader->getNodeType() == irr::io::EXN_ELEMENT_END)	{
			if( strcmp( mReader->getNodeName(), "library_lights") != 0)
				ThrowException( "Expected end of <library_lights> element.");

			break;
		}
	}
}
