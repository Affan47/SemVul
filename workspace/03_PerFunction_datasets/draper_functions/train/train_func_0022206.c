InitializeScripting()
{
    if (!m_pDBG->GetActiveConfigEx().GetFlag(DebuggerConfiguration::WatchScriptPrinters))
    {
        m_pDBG->DebugLog(_("Skip initializing the scripting!"));
        return;
    }


    if (!SquirrelVM::GetVMPtr())
    {
        m_pDBG->Log(_("Scripting engine not running. Debugger scripts disabled..."));
        return;
    }


    SqPlus::SQClassDef<GDB_driver>("GDB_driver").
            func(&GDB_driver::RegisterType, "RegisterType");


    wxString script = ConfigManager::LocateDataFile(_T("gdb_types.script"), sdScriptsUser | sdScriptsGlobal);
    if (!script.IsEmpty())
    {
        Manager::Get()->GetScriptingManager()->LoadScript(script);
        try
        {
            SqPlus::SquirrelFunction<void> f("RegisterTypes");
            f(this);
        }
        catch (SquirrelError e)
        {
            m_pDBG->Log(wxString::Format(_T("Invalid debugger script: '%s'"), script.c_str()));
            m_pDBG->Log(cbC2U(e.desc));

            Manager::Get()->GetScriptingManager()->DisplayErrors(&e);
        }
    }

    wxString StlDebugCommand(_T("source $DATAPATH/scripts/stl-views-1.0.3.gdb"));
    Manager::Get()->GetMacrosManager()->ReplaceMacros(StlDebugCommand);
    QueueCommand(new DebuggerCmd(this, StlDebugCommand));
}
