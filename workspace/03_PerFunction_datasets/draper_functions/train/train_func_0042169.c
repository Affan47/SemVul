ReadAssetInfo()
{
	if( mReader->isEmptyElement())
		return;

	while( mReader->read())
	{
		if( mReader->getNodeType() == irr::io::EXN_ELEMENT)
		{
			if( IsElement( "unit"))
			{

				const int attrIndex = TestAttribute( "meter");
				if (attrIndex == -1) {
					mUnitSize = 1.f;
				}
				else {
					mUnitSize = mReader->getAttributeValueAsFloat( attrIndex);
				}


				if( !mReader->isEmptyElement())
					SkipElement();
			}
			else if( IsElement( "up_axis"))
			{

				const char* content = GetTextContent();
				if( strncmp( content, "X_UP", 4) == 0)
					mUpDirection = UP_X;
				else if( strncmp( content, "Y_UP", 4) == 0)
					mUpDirection = UP_Y;
				else
					mUpDirection = UP_Z;


				TestClosing( "up_axis");
			} else
			{
				SkipElement();
			}
		}
		else if( mReader->getNodeType() == irr::io::EXN_ELEMENT_END)
		{
			if( strcmp( mReader->getNodeName(), "asset") != 0)
				ThrowException( "Expected end of <asset> element.");

			break;
		}
	}
}
