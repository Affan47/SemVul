read_FCNodeObject (char *p_id, SOIP_Fc_Node **p_node, SOIP_DB_Entry *p_entry)
{
   ISNS_DBKey key;
   int rval;

   if ( (p_id == NULL ) || (strlen(p_id) <= 0) )
      return (ERROR);

   key.tag = NODE_NAME_KEY;
   strcpy(key.val.node_key.v, p_id);
   rval = ISNSdbRead(&key,p_entry);
   *p_node = (SOIP_Fc_Node *)&p_entry->data;
   return rval;
}
