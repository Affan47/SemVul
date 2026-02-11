hard_flow_code_override(int eindex) const
{
    for (int i = _flow_code_override.size() - 1; i >= 0; --i)
	if (_flow_code_override_eindex[i] == eindex)
	    return _flow_code_override[i].c_str();
    return 0;
}
