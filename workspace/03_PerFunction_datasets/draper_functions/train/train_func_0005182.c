OnScriptModuleMenu(int id)
{
    ModuleMenuCallbacks::iterator it;
    it = s_MenuCallbacks.find(id);
    if (it != s_MenuCallbacks.end())
    {
        MenuCallback& callback = it->second;
        SqPlus::SquirrelFunction<void> f(callback.object, "OnModuleMenuClicked");
        if (!f.func.IsNull())
        {
            try
            {
                f(callback.menuIndex);
            }
            catch (SquirrelError e)
            {
                cbMessageBox(cbC2U(e.desc), _("Script error"), wxICON_ERROR);
            }
        }
    }
}
