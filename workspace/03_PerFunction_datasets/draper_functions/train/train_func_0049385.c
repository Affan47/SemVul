drsuapi_dissect_DsGetNCChangesCtr7(tvbuff_t *tvb, int offset, packet_info *pinfo _U_, proto_tree *parent_tree, dcerpc_info *di _U_, guint8 *drep _U_, int hf_index, guint32 param _U_)
{
    proto_item *item=NULL;
    int old_offset;

    old_offset=offset;
    if(parent_tree){
 	   item=proto_tree_add_item(parent_tree, hf_index, tvb, offset, -1, ENC_NA);
    }

    proto_item_set_len(item, offset-old_offset);

    return offset;
}
