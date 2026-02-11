ClearTree(int cc, GifTree *root)
{
  int i;
  GifTree *newNode, **xx;

  if (debugFlag>1) fprintf(stderr, "Clear Tree  cc= %d\n", cc);
  if (debugFlag>1) fprintf(stderr, "nodeCount = %d lookup nodes = %d\n", nodecount, lookuptypes);
  maxchainlen=0; lookuptypes = 1;
  nodecount = 0;
  nodeArray = root->node;
  xx= nodeArray;
  for (i = 0; i < noOfArrays; i++ ) {
    memmove (xx, empty, 256*sizeof(GifTree **));
    xx += 256;
  }
  topNode = baseNode;
  for(i=0; i<cc; i++) {
    root->node[i] = newNode = ++topNode;
    newNode->nxt = NULL;
    newNode->alt = NULL;
    newNode->code = i;
    newNode->ix = i;
    newNode->typ = TERMIN;
    newNode->node = empty;
    nodecount++;
  }
}
