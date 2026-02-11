read_PortalGroupObject (SOIP_Portal_Group_Key *p_portal_key, SOIP_Portal_Group **p_portal, SOIP_DB_Entry *p_entry)
{
   ISNS_DBKey key;
   int rval;

   if ( p_portal_key == NULL )
      return (ERROR);

   key.tag = PORTAL_GROUP_ID_KEY;
   __ISNS_COPY (&key.val.portal_group_key, sizeof(SOIP_Portal_Group_Key), p_portal_key, sizeof(SOIP_Portal_Group_Key));
   rval = ISNSdbRead(&key,p_entry);
   *p_portal = (SOIP_Portal_Group *)&p_entry->data;
   return rval;
}
