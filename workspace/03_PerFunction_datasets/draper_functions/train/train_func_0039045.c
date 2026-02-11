OverwriteParam(const string &paramName, PARAM_VEC values)
{
	VERBOSE(2,"Overwriting parameter " << paramName);

	m_setting[paramName];
	if (m_setting[paramName].size() > 1){
		VERBOSE(2," (the parameter had " << m_setting[paramName].size() << " previous values)");
		CHECK(m_setting[paramName].size() == values.size());
	}else{
		VERBOSE(2," (the parameter does not have previous values)");
		m_setting[paramName].resize(values.size());
	}
	VERBOSE(2," with the following values:");
	int i=0;
	for (PARAM_VEC::iterator iter = values.begin(); iter != values.end() ; iter++, i++){
		m_setting[paramName][i] = *iter;
		VERBOSE(2, " " << *iter);
	}
	VERBOSE(2, std::endl);
}
