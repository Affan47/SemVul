eina_quadtree_show(Eina_QuadTree_Item *object)
{
   EINA_MAGIC_CHECK_QUADTREE_ITEM(object, EINA_FALSE);

   object->quad->lost = EINA_TRUE;

   if (object->visible)
      return EINA_TRUE;

   object->visible = EINA_TRUE;
   if (!object->change)
      return eina_quadtree_change(object);

   return EINA_TRUE;
}
