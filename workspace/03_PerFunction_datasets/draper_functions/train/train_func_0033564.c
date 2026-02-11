writeFile (const char* const pszFilename)
{
  if (! m_pObject)
    return false;

  m_strFilename = pszFilename;

  CONDITION cond = DCM_WriteFile (&m_pObject, DCM_ORDERLITTLEENDIAN, pszFilename);
  if (cond != DCM_NORMAL) {
    m_bFail = true;
    m_strFailMessage = "Error writing DICOM file ";
    m_strFailMessage += pszFilename;
    return false;
  }

  return true;
}
