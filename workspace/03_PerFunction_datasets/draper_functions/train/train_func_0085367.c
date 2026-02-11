ExecuteCommand(
	enum CUserEvents::EventType event,
	const void* object,
	const wxString& cmd)
{

	wxString command = cmd;
	switch (event) {
		USEREVENTS_EVENTLIST()


	}
	if (!command.empty()) {
		CTerminationProcess *p = new CTerminationProcess(cmd);
		if (!wxExecute(command, wxEXEC_ASYNC, p)) {


			delete p;
			AddLogLineC(CFormat(_("Failed to execute command `%s' on `%s' event.")) %
				command % s_EventList[event].name);
		}
	}
}
