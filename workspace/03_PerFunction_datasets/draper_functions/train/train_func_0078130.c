operator()(const EventArgs& e) const
{
	ScriptModule* scriptModule = System::getSingleton().getScriptingModule();

	if (scriptModule)
	{
		return scriptModule->executeScriptedEventHandler(scriptFunctionName, e);
	}
	else
	{
		Logger::getSingleton().logEvent("Scripted event handler '" + scriptFunctionName + "' could not be called as no ScriptModule is available.", Errors);

		return false;
	}
}
