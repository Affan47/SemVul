ReadSPHState( vtkIdType vtkNotUsed(step) )
{
  LSDynaMetaData* p = this->P;


  p->Fam.SkipToWord(LSDynaFamily::TimeStepSection, p->CurrentState,0);
  p->Fam.SkipWords(p->SPHStateOffset);

#define VTK_LS_SPHARRAY(cond,celltype,arrayname,numComps)\
  if ( cond && this->GetCellArrayStatus( celltype, arrayname ) ) \
    { \
    this->Parts->AddProperty(celltype,arrayname,startPos,numComps); \
    } \
  startPos+=numComps;


  int startPos=0;
  VTK_LS_SPHARRAY(               false,LSDynaMetaData::PARTICLE,LS_ARRAYNAME_DEATH,1);
  VTK_LS_SPHARRAY(p->Dict["isphfg(2)"],LSDynaMetaData::PARTICLE,LS_ARRAYNAME_RADIUSOFINFLUENCE,1);
  VTK_LS_SPHARRAY(p->Dict["isphfg(3)"],LSDynaMetaData::PARTICLE,LS_ARRAYNAME_PRESSURE,1);
  VTK_LS_SPHARRAY(p->Dict["isphfg(4)"],LSDynaMetaData::PARTICLE,LS_ARRAYNAME_STRESS,6);
  VTK_LS_SPHARRAY(p->Dict["isphfg(5)"],LSDynaMetaData::PARTICLE,LS_ARRAYNAME_EPSTRAIN,1);
  VTK_LS_SPHARRAY(p->Dict["isphfg(6)"],LSDynaMetaData::PARTICLE,LS_ARRAYNAME_DENSITY,1);
  VTK_LS_SPHARRAY(p->Dict["isphfg(7)"],LSDynaMetaData::PARTICLE,LS_ARRAYNAME_INTERNALENERGY,1);
  VTK_LS_SPHARRAY(p->Dict["isphfg(8)"],LSDynaMetaData::PARTICLE,LS_ARRAYNAME_NUMNEIGHBORS,1);
  VTK_LS_SPHARRAY(p->Dict["isphfg(9)"],LSDynaMetaData::PARTICLE,LS_ARRAYNAME_STRAIN,6);
  VTK_LS_SPHARRAY(p->Dict["isphfg(10)"],LSDynaMetaData::PARTICLE,LS_ARRAYNAME_MASS,1);


  this->ReadCellProperties(LSDynaMetaData::PARTICLE,p->Dict["NUM_SPH_DATA"]);


#undef VTK_LS_SPHARRAY
  return 0;
}
