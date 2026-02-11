send_iscsi_scn_md(char *p_node_name, ISNS_Msg_Descp *p_md)
{
   int               foundSCNPortal;
   SOIP_DB_Entry     lentry;
   SOIP_DB_Entry     lentry2;
   SOIP_Iscsi        *p_node;
   SOIP_Entity       *p_entity;
   SOIP_Portal       *p_portal = NULL;
   ISNS_LIST_NODE    *lnode;
   ISNS_ATTR_VALS_CB *attr_vals_cb;
   int               rval;

   if ( p_node_name == NULL)
      return (ERROR);

   rval = read_ISCSIObject(p_node_name, &p_node, &lentry);
   if (rval != SUCCESS)
     return rval;

   if (!p_node->scn_bitmap)
      return (SUCCESS);


   if ( p_node->scn_callback )
   {


      attr_vals_cb = ISNSAttrGetList(p_md);
      if (attr_vals_cb != NULL)
      {
             p_node->scn_callback(attr_vals_cb);
      }

      ISNSFreeBuffer ((char *)attr_vals_cb->attr_val_sptr);
      ISNSFreeBuffer ((char *)attr_vals_cb);
   }
   else if ( p_node->scn_sockfd )
   {

      p_md->cb.sock.socketType = ISNS_SOCKET_TYPE_TCP;
      p_md->cb.sock.sockfd = p_node->scn_sockfd;

      if ( SUCCESS != ISNSSendMsg (p_md) )
      {
         __DEBUG(sns_scn_debug & 1, (Warning: Failure sending SCN));
         p_node->scn_bitmap = 0;

         write_ISCSIObject(p_node_name, lentry);
      }
   }
   else
   {

      char buffer[256]={0};


      memset (buffer, 0, sizeof (buffer));
      strncpy (buffer, p_node->entity_id.id, sizeof(buffer));
      read_EntityObject (buffer, &p_entity, &lentry);


      foundSCNPortal = FALSE;
      lnode = NULL;
      while ((lnode=GetNextNode(&p_entity->iportal_list, lnode)))
      {
         rval = read_PortalObject(GetNodeData(lnode), &p_portal, &lentry2);
         if (rval != SUCCESS)
             return rval;


         if (p_portal->esi_port != 0)
         {
            foundSCNPortal = TRUE;
            break;
         }
      }


      if (foundSCNPortal)
      {
         p_md->cb.sock.socketType = ISNS_SOCKET_TYPE_UDP;
         p_md->cb.sock.addr.sin_family = AF_INET;
         p_md->cb.sock.len = sizeof (p_md->cb.sock.addr);

         memcpy (&p_md->cb.sock.addr.sin_addr.s_addr,
                 p_portal->ip_addr.v + 12,
                 sizeof (p_md->cb.sock.addr.sin_addr.s_addr));

         p_md->cb.sock.addr.sin_port =
            htons ((short)(p_portal->esi_port & 0xFFFF));

         ISNSSendMsg (p_md);

      }
      else
      {
         __DEBUG (sns_scn_debug & 1, (No valid Portal to send SCN));
         return (ERROR);
      }

   }

   return (SUCCESS);
}
