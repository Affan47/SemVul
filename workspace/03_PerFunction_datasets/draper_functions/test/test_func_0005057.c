CompilerInheritsFrom(Compiler* compiler, const wxString& from_id)
{
    if (!compiler)
        return false;

    wxString id = compiler->GetID();
    if (id.Matches(from_id))
        return true;

    while (compiler)
    {
        id = compiler->GetParentID();
        if (id.Matches(from_id))
            return true;


        Compiler* newcompiler = GetCompiler(id);
        if (compiler == newcompiler)
        {
            Manager::Get()->GetLogManager()->DebugLog(_T("Compiler circular dependency detected?!?!?"));
            break;
        }
        compiler = newcompiler;
    }
    return false;
}
