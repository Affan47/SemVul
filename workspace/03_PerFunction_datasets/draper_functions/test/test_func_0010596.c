dumpStackTrace(std::ostringstream& out)
{
	if (m_call_stack.empty()) {
		return;
	}

	out << std::endl << "Stack trace:" << std::endl;

	do {
		const CallStackEntry& entry = m_call_stack.top();

		if (entry.loc) {
			if (entry.func) {
				out << "# " << entry.func->getName() << "()";
			} else {
				out << "# <main>";
			}

			if (entry.loc->begin.filename) {
				out << " at " << *entry.loc->begin.filename << ":";
			} else {
				out << " at <command line>:";
			}
			out << entry.loc->begin.line << std::endl;
		}

		m_call_stack.pop();
	} while (!m_call_stack.empty());
}
