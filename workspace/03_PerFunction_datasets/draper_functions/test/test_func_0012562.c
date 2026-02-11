Pete_Kaleidoscope_LinesSortFunction(const void* pElem1,const void* pElem2) {

  const SPete_Kaleidoscope_Line* pFirstLine;
  pFirstLine = reinterpret_cast<const SPete_Kaleidoscope_Line*>(pElem1);
  const SPete_Kaleidoscope_Line* pSecondLine;
  pSecondLine=reinterpret_cast<const SPete_Kaleidoscope_Line*>(pElem2);

  const float FirstYIsNeg=(pFirstLine->Y<0.0f);
  const float SecondYIsNeg=(pSecondLine->Y<0.0f);

  if (FirstYIsNeg!=SecondYIsNeg) {

    if (FirstYIsNeg) {
      return -1;
    } else {
      return 1;
    }

  } else {

    const float FirstX=pFirstLine->X;
    const float SecondX=pSecondLine->X;

    if (FirstX<SecondX) {
      return -1;
    } else if (FirstX>SecondX) {
      return 1;
    } else {
      return 0;
    }

  }

}
