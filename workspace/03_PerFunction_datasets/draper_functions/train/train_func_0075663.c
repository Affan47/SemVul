thrown_item(item *used)
{
 if (used == NULL) {
  debugmsg("npcmove.cpp's thrown_item() called with NULL item");
  return false;
 }
 itype_id type = itype_id(used->type->id);
 return (used->active || type == itm_knife_combat || type == itm_spear_wood);
}
