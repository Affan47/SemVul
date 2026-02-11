Compress ( LFA_FileRef sourceRef, LFA_FileRef destRef )
	{

		if ( this->IsCompressed() ) this->Encode ( sourceRef, destRef, CWS, Def );

	}
