Pete_Kaleidoscope_SetupLines(int* poutLinesCount) {

  const float MaxDivisions=((nMaxLines/2)-1.0f);

  float Divisions=ceilf(m_Divisions);
  if (Divisions<1.0f) {
    Divisions=1.0f;
  } else if (Divisions>MaxDivisions) {
    Divisions=MaxDivisions;
  }

  const int nDivisionsInt=static_cast<int>(Divisions);

  const float AnglePreIncrement=m_OutputAnglePreIncrement+0.001;

  const float AngleInterval=(Pete_TwoPi/Divisions);
  const float HalfAngleInterval=(AngleInterval*m_ReflectionLineProportion);

  const int nLinesCount=(nDivisionsInt*2);

  SPete_Kaleidoscope_Line* pLinesStart=reinterpret_cast<SPete_Kaleidoscope_Line*>(Pete_LockHandle(hLines));
  if (pLinesStart==NULL) {
    return;
  }


  SPete_Kaleidoscope_Line* pCurrentLine=pLinesStart;

  int nCurrentDivision;
  for (nCurrentDivision=0; nCurrentDivision<nDivisionsInt; nCurrentDivision+=1) {

    float StartAngle=
      AnglePreIncrement+(nCurrentDivision*AngleInterval);
    StartAngle=fmodf(StartAngle,Pete_TwoPi);

    pCurrentLine->X=cos(StartAngle);
    pCurrentLine->Y=sin(StartAngle);
    pCurrentLine->Flags=0;

    pCurrentLine+=1;

    float HalfAngle=(StartAngle+HalfAngleInterval);
    HalfAngle=fmodf(HalfAngle,Pete_TwoPi);

    pCurrentLine->X=cos(HalfAngle);
    pCurrentLine->Y=sin(HalfAngle);
    pCurrentLine->Flags=PETE_KALEIDOSCOPE_HALFLINE_BIT;

    pCurrentLine+=1;

  }

  *poutLinesCount=nLinesCount;

}
