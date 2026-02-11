CheckPointMitosis(void)
{
  const bool DNAProofRead = ( m_GenomeCopy && m_Genome );

  if ( !DNAProofRead )
    {
    std::cerr << "PANIC: DNA failed ! " << std::endl;
    }
  return DNAProofRead;
}
