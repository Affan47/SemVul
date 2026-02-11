ConvertMaterialForMesh(aiMesh* out, const Model& model, const MeshGeometry& geo,
		MatIndexArray::value_type materialIndex)
	{

		const std::vector<const Material*>& mats = model.GetMaterials();
		if (static_cast<unsigned int>(materialIndex) >= mats.size() || materialIndex < 0) {
			FBXImporter::LogError("material index out of bounds, setting default material");
			out->mMaterialIndex = GetDefaultMaterial();
			return;
		}

		const Material* const mat = mats[materialIndex];
		MaterialMap::const_iterator it = materials_converted.find(mat);
		if (it != materials_converted.end()) {
			out->mMaterialIndex = (*it).second;
			return;
		}

		out->mMaterialIndex = ConvertMaterial(*mat, &geo);
		materials_converted[mat] = out->mMaterialIndex;
	}
