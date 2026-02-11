Hlsl2Glsl_Translate(
	const ShHandle handle,
	const char* entry,
	ETargetVersion targetVersion,
	unsigned options)
{
   if (handle == 0)
      return 0;

   HlslCrossCompiler* compiler = handle;
   compiler->infoSink.info.erase();


   initializeHLSLSupportLibrary(targetVersion);

	if (!compiler->IsASTTransformed() || !compiler->IsGlslProduced())
	{
		compiler->infoSink.info.message(EPrefixError, "Shader does not have valid object code.");
		return 0;
	}

   bool ret = compiler->GetLinker()->link(compiler, entry, targetVersion, options);

   finalizeHLSLSupportLibrary();

   return ret ? 1 : 0;
}
