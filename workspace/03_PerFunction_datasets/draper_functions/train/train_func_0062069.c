ReadShader(Q3Shader::ShaderData& fill) const
{

	const std::string::size_type s = path.find_last_of("\\/",path.length()-2);
	const std::string model_file = path.substr(s+1,path.length()-(s+2));


	if (!configShaderFile.length()) {
		if(!Q3Shader::LoadShader(fill,path + "..\\..\\..\\scripts\\" + model_file + ".shader",mIOHandler)) {
			Q3Shader::LoadShader(fill,path + "..\\..\\..\\scripts\\" + filename + ".shader",mIOHandler);
		}
	}
	else {


		const std::string::size_type st = configShaderFile.find_last_of('.');
		if (st == std::string::npos) {

			if(!Q3Shader::LoadShader(fill,configShaderFile + model_file + ".shader",mIOHandler)) {
				Q3Shader::LoadShader(fill,configShaderFile + filename + ".shader",mIOHandler);
			}
		}
		else {
			Q3Shader::LoadShader(fill,configShaderFile,mIOHandler);
		}
	}
}
