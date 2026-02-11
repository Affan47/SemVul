idle()
{
	if (analy && analy->analy) {
		addrs = analy->analy->getLocationCount();
		labels = analy->analy->getSymbolCount();
		atype = analy->analy->getType();
		analy->analy->getName(aname);
		if (analy->analy->disasm) {
			adis = analy->analy->disasm->getName();
		} else {
			adis = "?";
		}
		dirtyview();
	}
	return false;
}
