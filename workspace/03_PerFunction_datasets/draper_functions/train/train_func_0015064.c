UseMake(cbProject* project)
{
    if (!project)
        project = m_pProject;
    if (!project)
        return false;
    wxString idx = project->GetCompilerID();
    if (CompilerFactory::GetCompiler(idx))
        return project->IsMakefileCustom();

    return false;
}
