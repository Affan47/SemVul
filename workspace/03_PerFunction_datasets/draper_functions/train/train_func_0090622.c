addArg(CmdLineOptionArg* arg) {
	m_Args.push_back(arg);
	arg->setOption(this);
	int nb = m_Args.size();
	if (m_MinNbArgs < nb) m_MinNbArgs = nb;
}
