EditGameFindRegion()
{
	ARegion *ret = 0;
	int x, y, z;
	AString *pStr = 0, *pToken = 0;
	Awrite("Region coords (x y z):");
	do {
		pStr = AGetString();

		pToken = pStr->gettoken();
		if(!pToken) {
			Awrite("No such region.");
			break;
		}
		x = pToken->value();
		SAFE_DELETE(pToken);

		pToken = pStr->gettoken();
		if(!pToken) {
			Awrite("No such region.");
			break;
		}
		y = pToken->value();
		SAFE_DELETE(pToken);

		pToken = pStr->gettoken();
		if(pToken) {
			z = pToken->value();
			SAFE_DELETE(pToken);
		} else {
			z = 0;
		}

		ARegion *pReg = regions.GetRegion(x, y, z);
		if(!pReg) {
			Awrite("No such region.");
			break;
		}

		ret = pReg;
	} while(0);

	if(pStr) delete pStr;
	if(pToken) delete pToken;

	return(ret);
}
