AssignFsmInternalID(GrcManager * pcman, int nPassID)
{
	if (!m_psymInput)

		return;

	if (m_psymInput->Data())
	{
		GdlGlyphClassDefn * pglfcIn = m_psymInput->GlyphClassDefnData();
		Assert(pglfcIn);
		pcman->AddToFsmClasses(pglfcIn, nPassID);
	}

}
