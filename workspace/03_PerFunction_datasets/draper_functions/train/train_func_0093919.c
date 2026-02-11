CanDeferToLastStep(const DocModification &mh) {
	if (mh.modificationType & (SC_MOD_BEFOREINSERT | SC_MOD_BEFOREDELETE))
		return true;
	if (!(mh.modificationType & (SC_PERFORMED_UNDO | SC_PERFORMED_REDO)))
		return false;
	if (mh.modificationType & SC_MULTISTEPUNDOREDO)
		return true;
	return false;
}
