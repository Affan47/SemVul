GetLODSize(vector<uint64_t>& vLODIndices) const {

  uint64_t ulSize = 0;

  vector<uint64_t> vReducedDomainSize;
  vReducedDomainSize.resize(ulDomainSemantics.size());


  for (size_t i=0;i<vReducedDomainSize.size();i++) {
    if(ulLODDecFactor[i] < 2)
      vReducedDomainSize[i]  = ulDomainSize[i];
    else
      vReducedDomainSize[i]  = max<uint64_t>(1,uint64_t(floor(double(ulDomainSize[i]) / double(MathTools::Pow(ulLODDecFactor[i],vLODIndices[size_t(ulLODGroups[i])])))));
  }

  ulSize = ComputeLODLevelSize(vReducedDomainSize);

  return ulSize;
}
