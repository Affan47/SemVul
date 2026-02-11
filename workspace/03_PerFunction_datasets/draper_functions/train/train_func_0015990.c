ConvertTransformOrder_TRStoSRT(aiQuatKey* out_quat, aiVectorKey* out_scale,
		aiVectorKey* out_translation,
		const KeyFrameListList& scaling,
		const KeyFrameListList& translation,
		const KeyFrameListList& rotation,
		const KeyTimeList& times,
		double& maxTime,
		double& minTime,
		Model::RotOrder order,
		const aiVector3D& def_scale,
		const aiVector3D& def_translate,
		const aiQuaternion& def_rotation)
	{
		if (!rotation.empty()) {
			InterpolateKeys(out_quat, times, rotation, false, maxTime, minTime, order);
		}
		else {
			for (size_t i = 0; i < times.size(); ++i) {
				out_quat[i].mTime = CONVERT_FBX_TIME(times[i]) * anim_fps;
				out_quat[i].mValue = def_rotation;
			}
		}

		if (!scaling.empty()) {
			InterpolateKeys(out_scale, times, scaling, true, maxTime, minTime);
		}
		else {
			for (size_t i = 0; i < times.size(); ++i) {
				out_scale[i].mTime = CONVERT_FBX_TIME(times[i]) * anim_fps;
				out_scale[i].mValue = def_scale;
			}
		}

		if (!translation.empty()) {
			InterpolateKeys(out_translation, times, translation, false, maxTime, minTime);
		}
		else {
			for (size_t i = 0; i < times.size(); ++i) {
				out_translation[i].mTime = CONVERT_FBX_TIME(times[i]) * anim_fps;
				out_translation[i].mValue = def_translate;
			}
		}

		const size_t count = times.size();
		for (size_t i = 0; i < count; ++i) {
			aiQuaternion& r = out_quat[i].mValue;
			aiVector3D& s = out_scale[i].mValue;
			aiVector3D& t = out_translation[i].mValue;

			aiMatrix4x4 mat, temp;
			aiMatrix4x4::Translation(t, mat);
			mat *= aiMatrix4x4( r.GetMatrix() );
			mat *= aiMatrix4x4::Scaling(s, temp);

			mat.Decompose(s, r, t);
		}
	}
