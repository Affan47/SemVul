beginUserAtomicGlob(void)
{


  m_atomicGlobCount++;
  xxx_UT_DEBUGMSG(("Begin Glob count %d \n", m_atomicGlobCount));
  if (m_atomicGlobCount > 1)
    {

      return;
    }

	PX_ChangeRecord * pcr = new PX_ChangeRecord_Glob(PX_ChangeRecord::PXT_GlobMarker,
													 PX_ChangeRecord_Glob::PXF_UserAtomicStart);
	UT_return_if_fail (pcr);


	m_history.addChangeRecord(pcr);
	m_pDocument->notifyListeners(NULL,pcr);
}
