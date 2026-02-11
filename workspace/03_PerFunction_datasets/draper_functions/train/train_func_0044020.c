compileShader(const char* dstfilename, const char* srcfilename, bool vertexShader)
{
	const char* originalShader = loadFile(srcfilename);
	if( !originalShader )
		return false;

	const glslopt_shader_type type = vertexShader ? kGlslOptShaderVertex : kGlslOptShaderFragment;

	glslopt_shader* shader = glslopt_optimize(gContext, type, originalShader, 0);
	if( !glslopt_get_status(shader) )
	{
		printf( "Failed to compile %s:\n\n%s\n", srcfilename, glslopt_get_log(shader));
		return false;
	}

	const char* optimizedShader = glslopt_get_output(shader);

	if( !saveFile(dstfilename, optimizedShader) )
		return false;

	delete[] originalShader;
	return true;
}
