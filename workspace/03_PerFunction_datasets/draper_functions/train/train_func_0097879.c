ISNS_Process_SCN ( ISNS_Msg_Descp *p_md, ISNS_Msg *p_rsp_msg )
{
    ISNS_LIST_NODE                 *cnode;
    ISNS_Attr                 *p_attr;
    ISNS_ATTR_VALS_CB         *attr_vals_cb;
    SOIP_Scn_Callback_Entry   *p_scn;

    p_attr = (ISNS_Attr *)&p_md->msg.payload;


    cnode = NULL;
    while ((cnode = GetNextNode(&scn_callback_list, cnode)))
    {

        p_scn = (SOIP_Scn_Callback_Entry *)GetNodeData(cnode);


        if (0 != strcmp((char *)&p_attr->val, p_scn->name.v))
            continue;


         if ( p_scn->scn_callback_func )
         {


            attr_vals_cb = ISNSAttrGetList(p_md);
            if ( attr_vals_cb != NULL )
            {
                   p_scn->scn_callback_func( attr_vals_cb );
            }

            ISNSFreeBuffer ( (char *)attr_vals_cb->attr_val_sptr );
            ISNSFreeBuffer ( (char *)attr_vals_cb );
         }
         else
         {

             __LOG_WARNING ("Not implemented.\n");
         }


         ISNSAppendKey( p_rsp_msg, ISNS_ISCSI_NODE_ID,
             PAD4( strlen( p_scn->name.v ) ), p_scn->name.v, 0 );
         break;
    }
    return (SUCCESS);
}
