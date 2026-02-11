get_builtin_variable_from_semantic(EAttribSemantic sem, ETargetVersion targetVersion)
{
	if (sem == EAttrSemInstanceID)
	{
		if (targetVersion == ETargetGLSL_ES_100)
			return "gl_InstanceIDEXT";
		if (targetVersion <= ETargetGLSL_140)
			return "gl_InstanceIDARB";
		return "gl_InstanceID";
	}
	if (sem == EAttrSemVertexID)
	{
		if (targetVersion != ETargetGLSL_ES_100)
			return "gl_VertexID";
	}
	return NULL;
}
