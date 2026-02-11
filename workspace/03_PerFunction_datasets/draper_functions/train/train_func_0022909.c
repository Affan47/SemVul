glp_set_obj_dir(glp_prob *lp, int dir)
{     glp_tree *tree = lp->tree;
      if (tree != NULL && tree->reason != 0)
         xerror("glp_set_obj_dir: operation not allowed\n");
     if (!(dir == GLP_MIN || dir == GLP_MAX))
         xerror("glp_set_obj_dir: dir = %d; invalid direction flag\n",
            dir);
      lp->dir = dir;
      return;
}
