CheckSelectors(GdlRule * prule, int , int crit)
{
	if (m_psymOutput->FitsSymbolType(ksymtClass) ||
		m_psymOutput->FitsSymbolType(ksymtSpecialAt))
	{
		if (m_pexpSelector)
		{

			if (m_pexpSelector->SlotNumber() <= 0)
			{
				g_errorList.AddError(1177, this,
					"Item ",
					PosString(),
					": invalid selector following '@'");
				m_pritSelInput = NULL;
				return;
			}
			else if (m_pexpSelector->SlotNumber() > crit)
			{
				g_errorList.AddError(1178, this,
					"Item ",
					PosString(),
					": selector out of range");
				m_pritSelInput = NULL;
				return;
			}
			else
			{
				m_pritSelInput = prule->Item(m_pexpSelector->SlotNumber() - 1);
			}

			if (!m_pritSelInput->m_psymInput->FitsSymbolType(ksymtClass))
			{
				if (m_pritSelInput->m_psymInput->FitsSymbolType(ksymtSpecialLb))
				{
				}
				else
					g_errorList.AddError(1179, this,
						"Item ",
						PosString(),
						": input not specified for slot indicated by selector");
			}
		}
		else
		{
			m_pritSelInput = this;
		}

	}
	else
	{
		if (m_pexpSelector)
		{
			g_errorList.AddError(1180, this,
				"Item ",
				PosString(),
				": selectors can only be used with class names and '@'");
			delete m_pexpSelector;
			m_pexpSelector = NULL;
		}

		m_pritSelInput = NULL;
	}

}
