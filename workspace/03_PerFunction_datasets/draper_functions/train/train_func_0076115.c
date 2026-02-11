SetRegTypes(ARegionArray *pRegs, int newType)
{
	for(int i = 0; i < pRegs->x; i++) {
		for(int j = 0; j < pRegs->y; j++) {
			ARegion *reg = pRegs->GetRegion(i, j);
			if(!reg) continue;
			if(reg->type == -1) reg->type = newType;
		}
	}
}
