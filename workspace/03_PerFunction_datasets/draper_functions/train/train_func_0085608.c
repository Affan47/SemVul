ReadWorld(TempScope& scope)
{
	while (ReadElementUpToClosing("world"))	{
		const std::string& s = GetElementName();


		if (s == "lighting") {
			ReadLighting(scope);
		}
		else if (s == "object" || s == "mesh" || s == "mat") {
			break;
		}
	}


	aiNode* const nd = ReadObject(scope,true,"world");
	if(!nd) {
		ThrowException("failure reading <world>");
	}
	if(!nd->mName.length) {
		nd->mName.Set("WORLD");
	}

	scene->mRootNode = nd;
}
