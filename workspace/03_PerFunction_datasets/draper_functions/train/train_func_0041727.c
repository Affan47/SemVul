tryadd(node *p, node **item, node **nufork)
{


  long pos;
  boolean found;

  add(p, *item, *nufork, &root, treenode);
  evaluate(root);
  if (lastrearr) {
    if (like >= bstlike2) {
      savetree();
      if (like > bstlike2) {
        bestlike = bstlike2 = like;
        pos = 1;
        nextree = 1;
        dollop_addtree(&pos);
      } else {
        pos = 0;
        findtree(&found, &pos, nextree, place, bestrees);


        if (!found) {
          if (nextree <= maxtrees)
            dollop_addtree(&pos);
        }
      }
    }
  }
  if (like > bestyet) {
    bestyet = like;
    there = p;
  }
  re_move(item, nufork, &root, treenode);
}
