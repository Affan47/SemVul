serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options) const
	{
		out->addInt("ValInt", ValInt);
		out->addFloat("ValFloat", ValFloat);
		out->addString("ValString", ValString.c_str());
		out->addString("ValStringW", ValStringW.c_str());
		out->addBinary("ValBinary", (void*)ValBinary, BINARY_BLOCK_SIZE);
		out->addArray("ValStringWArray", ValStringWArray);
		out->addBool("ValBool", ValBool);
		out->addEnum("ValEnum", ValEnum, MockEnumNames);
		out->addColor("ValColor", ValColor);
		out->addColorf("ValColorf", ValColorf);
		out->addVector3d("ValVector3df", ValVector3df);
		out->addVector2d("ValVector2df", ValVector2df);
		out->addDimension2d("ValDimension2du", ValDimension2du);
		out->addPosition2d("ValPosition2di", ValPosition2di);
		out->addRect("ValRect", ValRect);
		out->addMatrix("ValMatrix", ValMatrix);
		out->addQuaternion("ValQuaternion", ValQuaternion);
		out->addBox3d("ValAabbox3df", ValAabbox3df);
		out->addPlane3d("ValPlane3df", ValPlane3df);
		out->addTriangle3d("ValTriangle3df", ValTriangle3df);
		out->addLine2d("ValLine2df", ValLine2df);
		out->addLine3d("ValLine3df", ValLine3df);
		out->addTexture("ValTexture", ValTexture );
		out->addUserPointer("ValPointer", ValPointer);
	}
