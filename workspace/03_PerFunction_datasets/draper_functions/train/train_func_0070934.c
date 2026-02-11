getName(int var) {
	if (check(&var)) {
		return (char*)m_LocalMap->var_name(var).c_str();
	} else {
		return (char*)m_GlobalMap.var_name(var).c_str();
	}
}
