CheckInputClass()
{
	for (size_t iritT = 0; iritT < m_vprit.size(); iritT++)
	{
		Symbol psymInput = m_vprit[iritT]->m_psymInput;

		if (!psymInput)
		{
			g_errorList.AddError(1170, this,
				"Mismatched items between lhs and rhs");
			psymInput = g_cman.SymbolTable()->FindSymbol("_");
			m_vprit[iritT]->m_psymInput = psymInput;
		}

		if (!psymInput->FitsSymbolType(ksymtClass) &&
			!psymInput->FitsSymbolType(ksymtSpecialLb))
		{

			Assert(psymInput->FitsSymbolType(ksymtSpecialUnderscore));

			GdlSubstitutionItem * pritsub = dynamic_cast<GdlSubstitutionItem*>(m_vprit[iritT]);
			if (pritsub)
			{
				Symbol psymOutput = pritsub->OutputSymbol();
				if (!psymOutput ||
					(!psymOutput->FitsSymbolType(ksymtClass) &&
						(!psymOutput->FitsSymbolType(ksymtSpecialAt))))
					g_errorList.AddError(1171, this,
						"Item ",
						pritsub->PosString(),
						": no input or output class specified");
			}
			else
				g_errorList.AddError(1172, this,
					"Mismatched items among context, lhs and/or rhs");
		}
	}
}
