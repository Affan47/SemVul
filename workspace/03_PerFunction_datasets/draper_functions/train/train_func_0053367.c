Validate()
	{

		if(pIndent)
			pIndent->isValid = true;
		if(pMapStart)
			pMapStart->status = Token::VALID;
		if(pKey)
			pKey->status = Token::VALID;
	}
