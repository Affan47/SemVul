prepareAOMap(const BasisInfoStruct& bis, const int *shellMap, int *aoMap)
{
  int newIdx = 0;
  for(int i=0; i< bis.noOfShells; i++) {
    const ShellSpecStruct& shell = bis.shellList[shellMap[i]];
    for(int ao=0; ao<shell.noOfBasisFuncs; ao++) {
      aoMap[newIdx+ao] = shell.startIndexInMatrix+ao;

    }
    newIdx += shell.noOfBasisFuncs;
  }
}
