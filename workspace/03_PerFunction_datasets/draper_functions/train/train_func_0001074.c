copytree()
{

  if (whichtree == 1)
    othertree = 0;
  else
    othertree = 1;

  treesets[othertree].root = copytrav(root);
  treesets[othertree].nonodes = nonodes;
  treesets[othertree].waswritten = waswritten;
  treesets[othertree].hasmult = hasmult;
  treesets[othertree].haslengths = haslengths;
  treesets[othertree].nolengths = nolengths;
  treesets[othertree].initialized = true;

}
