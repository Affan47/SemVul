gen_subroutine_call_polish_arg(GLESubCallInfo* info, int i, GLEPcode& pcode) throw(ParserError) {
	GLESub* sub = info->getSub();
	try {
		int vtype = sub->getParamType(i);
		m_polish->polish(info->getParamVal(i).c_str(), pcode, &vtype);
	} catch (ParserError err) {
		if (info->getParamPos(i) != -2) {

			err.incColumn(info->getParamPos(i)-1);
		} else {

			err.setParserString(info->getParamVal(i));
		}
		throw err;
	}
}
