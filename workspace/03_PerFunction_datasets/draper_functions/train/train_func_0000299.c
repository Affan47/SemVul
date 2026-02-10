drsuapi_dissect_DsReplicaCoursor3Ctr(tvbuff_t *tvb, int offset, packet_info *pinfo _U_, proto_tree *parent_tree, dcerpc_info *di _U_, guint8 *drep _U_, int hf_index, guint32 param _U_)
{
    proto_item *item=NULL;
    proto_tree *tree=NULL;
    int old_offset;

    ALIGN_TO_8_BYTES;

    old_offset=offset;
    if(parent_tree){
 	   item=proto_tree_add_item(parent_tree, hf_index, tvb, offset, -1, ENC_NA);
 	   tree=proto_item_add_subtree(item, ett_drsuapi_DsReplicaCoursor3Ctr);
    }

    offset=drsuapi_dissect_DsReplicaCoursor3Ctr_count(tvb, offset, pinfo, tree, di, drep);

    offset=drsuapi_dissect_DsReplicaCoursor3Ctr_enumeration_context(tvb, offset, pinfo, tree, di, drep);

    offset=ucarray_drsuapi_dissect_DsReplicaCoursor3Ctr_array(tvb, offset, pinfo, tree, di, drep);

    proto_item_set_len(item, offset-old_offset);

    return offset;
}
