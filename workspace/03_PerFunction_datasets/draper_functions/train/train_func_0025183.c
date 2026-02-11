GetMachineClasses(FsmMachineClass ** ppfsmcAssignments,
	FsmMachineClassSet & setpfsmc)
{
	GdlGlyphClassDefn * pglfc = m_psymInput->GlyphClassDefnData();
	if (!pglfc)
		return;

	pglfc->GetMachineClasses(ppfsmcAssignments, setpfsmc);
}
