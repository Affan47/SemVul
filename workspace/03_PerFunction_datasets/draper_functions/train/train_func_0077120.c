butc_dissect_tciStatusS(tvbuff_t *tvb, int offset, packet_info *pinfo _U_, proto_tree *parent_tree, dcerpc_info *di _U_, guint8 *drep _U_, int hf_index, guint32 param _U_)
{
    proto_item *item=NULL;
    proto_tree *tree=NULL;
    int old_offset;

    ALIGN_TO_4_BYTES;

    old_offset=offset;
    if(parent_tree){
 	   item=proto_tree_add_item(parent_tree, hf_index, tvb, offset, -1, ENC_NA);
 	   tree=proto_item_add_subtree(item, ett_butc_tciStatusS);
    }

    offset=butc_dissect_tciStatusS_taskName(tvb, offset, pinfo, tree, di, drep);

    offset=butc_dissect_tciStatusS_flags(tvb, offset, pinfo, tree, di, drep);

    offset=butc_dissect_tciStatusS_lastPolled(tvb, offset, pinfo, tree, di, drep);

    offset=butc_dissect_tciStatusS_info(tvb, offset, pinfo, tree, di, drep);

    offset=butc_dissect_tciStatusS_taskId(tvb, offset, pinfo, tree, di, drep);

    offset=butc_dissect_tciStatusS_spare2(tvb, offset, pinfo, tree, di, drep);

    offset=butc_dissect_tciStatusS_spare3(tvb, offset, pinfo, tree, di, drep);

    offset=butc_dissect_tciStatusS_spare4(tvb, offset, pinfo, tree, di, drep);

    proto_item_set_len(item, offset-old_offset);

    return offset;
}
