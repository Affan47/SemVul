set_info(treeptr p, treeptr parent, sint pleaf, char *pname, float pdist)
{
   p->parent = parent;
   p->leaf = pleaf;
   p->dist = pdist;
   p->order = 0;
   strcpy(p->name, pname);
   if (p->leaf == TRUE)
     {
        p->left = NULL;
        p->right = NULL;
     }
}
