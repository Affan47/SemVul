ReadMaterial(TempScope& scope)
{
	const unsigned int mat_id = ReadIDAttr();

	ScopeGuard<aiMaterial> mat(new aiMaterial());
	while (ReadElementUpToClosing("mat"))  {
		const std::string& s = GetElementName();
		if (s == "amb") {
			const aiColor3D c = ReadCol3();
			mat->AddProperty(&c,1,AI_MATKEY_COLOR_AMBIENT);
		}
		else if (s == "diff") {
			const aiColor3D c = ReadCol3();
			mat->AddProperty(&c,1,AI_MATKEY_COLOR_DIFFUSE);
		}
		else if (s == "spec") {
			const aiColor3D c = ReadCol3();
			mat->AddProperty(&c,1,AI_MATKEY_COLOR_SPECULAR);
		}
		else if (s == "emiss") {
			const aiColor3D c = ReadCol3();
			mat->AddProperty(&c,1,AI_MATKEY_COLOR_EMISSIVE);
		}
		else if (s == "alpha") {
			const float f = ReadFloat();
			mat->AddProperty(&f,1,AI_MATKEY_OPACITY);
		}
		else if (s == "shine") {
			const float f = ReadFloat();
			mat->AddProperty(&f,1,AI_MATKEY_SHININESS);
		}
	}

	scope.materials[mat_id] = mat;
	scope.materials_linear.push_back(mat.dismiss());
}
