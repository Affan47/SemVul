object_message_add(lListElem *this_elem, int name,
                   u_long32 type, const char *message)
{
   bool ret = true;

   DENTER(TOP_LAYER, "object_message_add");
   if (this_elem != NULL) {
      lList *qim_list = NULL;

      lXchgList(this_elem, name, &qim_list);
      ret &= qim_list_add(&qim_list, type, message);
      lXchgList(this_elem, name, &qim_list);
   }
   DEXIT;
   return ret;
}
