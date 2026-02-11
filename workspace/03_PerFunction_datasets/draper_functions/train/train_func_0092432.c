UnregisterCompilers()
{
    WX_CLEAR_ARRAY(CompilerFactory::Compilers);
    CompilerFactory::Compilers.Empty();
    Compiler::m_CompilerIDs.Empty();

    s_DefaultCompiler = nullptr;
}
