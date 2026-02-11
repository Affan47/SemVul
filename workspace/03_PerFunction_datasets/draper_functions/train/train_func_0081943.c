GetPlugin(HSQUIRRELVM v)
{
    StackHandler sa(v);


    const wxString& name = *SqPlus::GetInstance<wxString,false>(v, 2);


    ScriptPlugins::iterator it = s_ScriptPlugins.find(name);
    if (it != s_ScriptPlugins.end())
    {

        return sa.Return(it->second);
    }


    return sa.Return();
}
