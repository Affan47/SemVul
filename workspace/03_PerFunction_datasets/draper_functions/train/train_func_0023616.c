AddCompilerDirs(cbProject* project, ParserBase* parser)
{
    if (!parser)
        return false;

    TRACE(_T("NativeParser::AddCompilerDirs(): Enter"));


    if (!project)
    {
        Compiler* compiler = CompilerFactory::GetDefaultCompiler();
        if (compiler)
        {

            AddIncludeDirsToParser(compiler->GetIncludeDirs(), wxEmptyString, parser);

            if (compiler->GetID().Contains(_T("gcc")))
                AddGCCCompilerDirs(compiler->GetMasterPath(), compiler->GetPrograms().CPP, parser);
        }
        TRACE(_T("NativeParser::AddCompilerDirs(): Leave"));
        return true;
    }


    wxString base = project->GetBasePath();
    parser->AddIncludeDir(base);
    TRACE(_T("NativeParser::AddCompilerDirs(): Adding project base dir to parser: ") + base);


    Compiler* compiler = CompilerFactory::GetCompiler(project->GetCompilerID());
    cb::shared_ptr<CompilerCommandGenerator> generator(compiler ? compiler->GetCommandGenerator(project) : nullptr);
    if (compiler && generator)
        generator->Init(project);


    AddIncludeDirsToParser(project->GetIncludeDirs(), base, parser);


    int nCompilers = 1 + project->GetBuildTargetsCount();
    Compiler** Compilers = new Compiler* [nCompilers];
    memset(Compilers, 0, sizeof(Compiler*) * nCompilers);
    nCompilers = 0;


    for (int i = 0; i < project->GetBuildTargetsCount(); ++i)
    {
        ProjectBuildTarget* target = project->GetBuildTarget(i);
        if (target && target->SupportsCurrentPlatform())
        {

            if (compiler && generator)
                AddIncludeDirsToParser(generator->GetCompilerSearchDirs(target), base, parser);


            AddIncludeDirsToParser(target->GetIncludeDirs(), base, parser);


            wxString CompilerIndex = target->GetCompilerID();
            Compiler* tgtCompiler = CompilerFactory::GetCompiler(CompilerIndex);
            if (tgtCompiler)
            {
                Compilers[nCompilers] = tgtCompiler;
                ++nCompilers;
            }
        }
    }


    if (compiler)
    {


        Compilers[nCompilers++] = compiler;
    }


    for (int idxCompiler = 0; idxCompiler < nCompilers; ++idxCompiler)
    {
        compiler = Compilers[idxCompiler];
        if (!compiler) continue;

        AddIncludeDirsToParser(compiler->GetIncludeDirs(), base, parser);


        wxString CompilerID = compiler->GetID();
        if (CompilerID.Contains(_T("gcc")))
            AddGCCCompilerDirs(Compilers[idxCompiler]->GetMasterPath(), compiler->GetPrograms().CPP, parser);
    }

    if (!nCompilers)
        CCLogger::Get()->DebugLog(_T("NativeParser::AddCompilerDirs(): No compilers found!"));

    delete [] Compilers;
    TRACE(_T("NativeParser::AddCompilerDirs(): Leave"));
    return true;
}
