AddCommand(CCommandTree* command)
{
	command->m_parent = this;
	const wxString& cmd = command->m_command;
	CmdPos_t it;
	for (it = m_subcommands.begin(); it != m_subcommands.end(); ++it) {
		if ((*it)->m_command > cmd) {
			break;
		}
	}
	m_subcommands.insert(it, command);
	return command;
}
