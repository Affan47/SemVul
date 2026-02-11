ScriptOfState(int state) {
	if ((state >= SCE_HP_START) && (state <= SCE_HP_IDENTIFIER)) {
		return eScriptPython;
	} else if ((state >= SCE_HB_START) && (state <= SCE_HB_STRINGEOL)) {
		return eScriptVBS;
	} else if ((state >= SCE_HJ_START) && (state <= SCE_HJ_REGEX)) {
		return eScriptJS;
	} else if ((state >= SCE_HPHP_DEFAULT) && (state <= SCE_HPHP_COMMENTLINE)) {
		return eScriptPHP;
	} else if ((state >= SCE_H_SGML_DEFAULT) && (state < SCE_H_SGML_BLOCK_DEFAULT)) {
		return eScriptSGML;
	} else if (state == SCE_H_SGML_BLOCK_DEFAULT) {
		return eScriptSGMLblock;
	} else {
		return eScriptNone;
	}
}
