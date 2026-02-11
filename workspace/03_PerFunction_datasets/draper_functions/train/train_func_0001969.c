ParseDataObjectAnimationKey( AnimBone* pAnimBone)
{
	readHeadOfDataObject();


	unsigned int keyType = ReadInt();


	unsigned int numKeys = ReadInt();

	for( unsigned int a = 0; a < numKeys; a++)
	{

		unsigned int time = ReadInt();


		switch( keyType)
		{
			case 0:
			{

				if( ReadInt() != 4)
					ThrowException( "Invalid number of arguments for quaternion key in animation");

				aiQuatKey key;
				key.mTime = double( time);
				key.mValue.w = ReadFloat();
				key.mValue.x = ReadFloat();
				key.mValue.y = ReadFloat();
				key.mValue.z = ReadFloat();
				pAnimBone->mRotKeys.push_back( key);

				CheckForSemicolon();
				break;
			}

			case 1:
			case 2:
			{

				if( ReadInt() != 3)
					ThrowException( "Invalid number of arguments for vector key in animation");

				aiVectorKey key;
				key.mTime = double( time);
				key.mValue = ReadVector3();

				if( keyType == 2)
					pAnimBone->mPosKeys.push_back( key);
				else
					pAnimBone->mScaleKeys.push_back( key);

				break;
			}

			case 3:
			case 4:
			{

				if( ReadInt() != 16)
					ThrowException( "Invalid number of arguments for matrix key in animation");


				MatrixKey key;
				key.mTime = double( time);
				key.mMatrix.a1 = ReadFloat(); key.mMatrix.b1 = ReadFloat();
				key.mMatrix.c1 = ReadFloat(); key.mMatrix.d1 = ReadFloat();
				key.mMatrix.a2 = ReadFloat(); key.mMatrix.b2 = ReadFloat();
				key.mMatrix.c2 = ReadFloat(); key.mMatrix.d2 = ReadFloat();
				key.mMatrix.a3 = ReadFloat(); key.mMatrix.b3 = ReadFloat();
				key.mMatrix.c3 = ReadFloat(); key.mMatrix.d3 = ReadFloat();
				key.mMatrix.a4 = ReadFloat(); key.mMatrix.b4 = ReadFloat();
				key.mMatrix.c4 = ReadFloat(); key.mMatrix.d4 = ReadFloat();
				pAnimBone->mTrafoKeys.push_back( key);

				CheckForSemicolon();
				break;
			}

			default:
				ThrowException( boost::str( boost::format( "Unknown key type %1% in animation.") % keyType));
				break;
		}


		CheckForSeparator();
	}

	CheckForClosingBrace();
}
