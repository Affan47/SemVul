SNSRemovePortalEntry (SOIP_Portal_Key *portal_key, ISNS_Attr * src_attr,
                      ISNS_Msg * p_rspmsg)
{
   SOIP_Portal       *p_portal;
   SOIP_Entity       *p_entity;
   int               rval;
   ISNS_LIST_NODE    *pnode;
   ISNS_LIST_NODE    *pnode2;
   PORTAL_LIST_ENTRY portalListEntry;
   char              *p_iscsi_name;

   __DEBUG (isns_dereg_debug & 1, (Deregistering Portal));

   memset(p_scn_all_msg_buffer, 0, sizeof(ISNS_Msg));
   p_scn_all_msg_buffer->hdr.type = ISNS_SCN;

   rval = read_PortalObject(portal_key, &p_portal, &entry2);
   if (rval != SUCCESS)
   {
    __DEBUG(isns_dereg_debug &1, Portal not found:%i,rval);
    return rval;
   }


   __DEBUG (isns_dereg_debug &1,(Remove Cert));

   RemoveCert (&p_portal->ptr_cert);

   delete_PortalidxObject(p_portal->portal_index);

   iSNS_stats.num_portals--;

   rval = read_EntityObject(p_portal->entity_id.id, &p_entity, &entry4);
   if (rval != SUCCESS)
      return rval;


   __ISNS_COPY (&portalListEntry.portal_ip_port, sizeof(portalListEntry.portal_ip_port), portal_key,
             sizeof(portalListEntry.portal_ip_port));
   portalListEntry.portal_idx = p_portal->portal_index;

   pnode = NULL;
   if ((pnode=FindNode(&p_entity->iportal_list, (char *)&portalListEntry, sizeof (portalListEntry))))
   {
         RemoveNode(&p_entity->iportal_list, pnode);
   }

   rval = write_EntityObject(p_portal->entity_id.id, entry4);


   pnode2 = NULL;
   while ( (pnode2 = GetNextNode( &p_entity->iscsi_node_list, pnode2)) )
   {
         p_iscsi_name = (char *) GetNodeData( pnode2 );
         send_iscsi_scn_to_members ( NULL, p_iscsi_name, p_scn_all_msg_buffer, ISNS_SCN_OBJ_REMOVED );
   }

   rval = delete_PortalObject(portal_key);
   if ( rval != SUCCESS)
      __LOG_ERROR ("ERROR: Portal DEREG Failed.");

   return (rval);
}
