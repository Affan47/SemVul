assignTimeSlots( HANDLE_SBR_DEC hSbrDec,
                             int noCols,
                             int useLP )
{

  hSbrDec->useLP = useLP;
  if (useLP) {
    hSbrDec->SynthesisQMF.flags |= QMF_FLAG_LP;
    hSbrDec->AnalysiscQMF.flags |= QMF_FLAG_LP;
  } else {
    hSbrDec->SynthesisQMF.flags &= ~QMF_FLAG_LP;
    hSbrDec->AnalysiscQMF.flags &= ~QMF_FLAG_LP;
  }
  if (!useLP)
    assignHqTimeSlots( hSbrDec, hSbrDec->QmfBufferReal, hSbrDec->QmfBufferImag, noCols );
  else
  {
    assignLcTimeSlots( hSbrDec, hSbrDec->QmfBufferReal, noCols );
  }
}
