ReadPartTitlesFromRootFile()
{


  LSDynaMetaData* p = this->P;
  if ( p->PreStateSize <= 0 )
    {
    vtkErrorMacro( "Database has bad pre state size(" << p->PreStateSize << ")." );
    return 1;
    }


  vtkIdType currentFileLoc = p->Fam.GetCurrentFWord();
  vtkIdType currentAdaptLevel = p->Fam.GetCurrentAdaptLevel();

  p->Fam.BufferChunk( LSDynaFamily::Float, 1 );
  double eofM = p->Fam.GetNextWordAsFloat();
  if(eofM !=LSDynaFamily::EOFMarker)
    {

    p->Fam.SkipToWord(LSDynaFamily::ControlSection,currentAdaptLevel,currentFileLoc);
    return 1;
    }


  vtkIdType numParts = p->PartIds.size();
  vtkIdType partTitlesByteSize = p->Fam.GetWordSize() * (2 + numParts);
  partTitlesByteSize += (numParts * 72);

  vtkIdType fileSize = p->Fam.GetFileSize(0);
  if ( fileSize < partTitlesByteSize + p->Fam.GetCurrentFWord())
    {

    p->Fam.SkipToWord(LSDynaFamily::ControlSection,currentAdaptLevel,currentFileLoc);
    return 1;
    }


  p->Fam.SkipWords(2);
  vtkIdType nameWordSize = 72 / p->Fam.GetWordSize();
  for(vtkIdType i=0; i < numParts; ++i)
    {
    p->Fam.BufferChunk(LSDynaFamily::Int, 1);
    p->Fam.GetNextWordAsInt();

    p->Fam.BufferChunk( LSDynaFamily::Char, nameWordSize);
    std::string name(p->Fam.GetNextWordAsChars(),72);
    if(name.size() > 0 && name[0]!=' ')
      {

      size_t found = name.find_last_not_of(' ');
      if(found != std::string::npos)
        {
        name = name.substr(0,found+1);
        }

      p->PartNames[i] = name;
      }
    }
  p->Fam.SkipToWord(LSDynaFamily::ControlSection,currentAdaptLevel,currentFileLoc);
  return 0;
}
