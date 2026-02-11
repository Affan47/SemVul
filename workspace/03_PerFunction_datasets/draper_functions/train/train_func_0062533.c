GeomBSPTreeDraw(Geom *geom)
{
  BSPTree *tree = geom->bsptree;

  if (tree == NULL || !(geom->geomflags & GEOM_ALPHA)) {
    return NULL;
  }


  if (tree->tree == NULL) {
    if (tree->init_lpl == NULL) {
      GeomBSPTree((Geom *)geom, tree, BSPTREE_ADDGEOM);
    }
    BSPTreeFinalize(tree);
  }

  mgbsptree(tree);

  if (tree->oneshot) {


    BSPTreeFreeTree(tree);
  }

  return geom;
}
