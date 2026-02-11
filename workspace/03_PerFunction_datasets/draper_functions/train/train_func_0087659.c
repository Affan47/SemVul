getSimplePrimitivesAll(const IntegralInfo& integralInfo)
{
  BasisFuncStruct* currBasisFunc;
  int nbast = this->noOfBasisFuncs;
  int maxNoOfSimplePrimsTot = nbast * MAX_NO_OF_PRIMITIVES_PER_BASIS_FUNC;
  DistributionSpecStruct* list = new DistributionSpecStruct[maxNoOfSimplePrimsTot];


  int n = 0;
  for(int i = 0; i < nbast; i++) {
    currBasisFunc = &basisFuncList[i];
    int noOfPrimitives = get_simple_primitives(currBasisFunc,
					       list,
					       n,
					       maxNoOfSimplePrimsTot,
					       integralInfo,
                                               use_6_d_funcs);
    if(noOfPrimitives <= 0) {
      do_output(LOG_CAT_ERROR, LOG_AREA_INTEGRALS, "error in get_simple_primitives");
      return -1;
    }
    currBasisFunc->noOfSimplePrimitives = noOfPrimitives;
    currBasisFunc->simplePrimitiveIndex = n;
    n += noOfPrimitives;
  }
  if(simplePrimitiveList) {
    printf("Releasing old simple primitive list\n");
    delete []simplePrimitiveList;
  }
  this->simplePrimitiveList = new DistributionSpecStruct[n];
  memcpy(this->simplePrimitiveList, list, n * sizeof(DistributionSpecStruct));
  delete [] list;
  this->noOfSimplePrimitives = n;
  return 0;
}
