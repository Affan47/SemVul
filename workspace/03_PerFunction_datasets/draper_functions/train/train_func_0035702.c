markDuplicatedInSemantics(GlslFunction* func)
{
	int pCount = func->getParameterCount();
	for (int ase = EAttrSemNone; ase < EAttrSemCount; ++ase)
	{
		std::vector<GlslSymbolOrStructMemberBase*> symsUsingSem;
		for (int ii=0; ii<pCount; ii++)
		{
			GlslSymbol *sym = func->getParameter(ii);
			appendDuplicatedInSemantics(sym, static_cast<EAttribSemantic>(ase), symsUsingSem);
		}
		if (symsUsingSem.size() > 1)
		{
			int index_of_largest = -1;
			int largest_array_size = 0;
			GlslSymbolOrStructMemberBase* sym_of_largest = 0;
			for (unsigned int ii=0; ii < symsUsingSem.size(); ii++)
			{
				if (!ii || largest_array_size < getElements(symsUsingSem[ii]->type))
				{
					index_of_largest = ii;
					sym_of_largest = symsUsingSem[ii];
					largest_array_size = getElements(symsUsingSem[ii]->type);
				}
			}
			for (unsigned int ii=0; ii < symsUsingSem.size(); ii++)
			{
				if (ii != index_of_largest)
				{
					symsUsingSem[ii]->suppressOutput(sym_of_largest);
				}
			}
		}
	}
}
