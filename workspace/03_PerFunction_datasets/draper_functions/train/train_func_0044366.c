_cmap_cmp_node_cb(const Eina_Rbtree *left, const Eina_Rbtree *right, void *data __UNUSED__)
{
   CMap *lcm;
   CMap *rcm;

   lcm = EINA_RBTREE_CONTAINER_GET(left, CMap);
   rcm = EINA_RBTREE_CONTAINER_GET(right, CMap);

   if (strcmp(lcm->str, rcm->str) < 0)
     return EINA_RBTREE_LEFT;
   return EINA_RBTREE_RIGHT;
}
