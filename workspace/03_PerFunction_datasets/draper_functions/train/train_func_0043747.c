decode_Tango_ChangeEventProp_st(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, proto_item *item _U_, int *offset _U_, MessageHeader *header _U_, const gchar *operation _U_, gboolean stream_is_big_endian _U_)
{


    guint32   u_octet4_loop_Tango_ChangeEventProp_extensions;
    guint32   i_Tango_ChangeEventProp_extensions;


    (void)item;

    giop_add_CDR_string(tree, tvb, offset, stream_is_big_endian, boundary, hf_Tango_ChangeEventProp_rel_change);

    giop_add_CDR_string(tree, tvb, offset, stream_is_big_endian, boundary, hf_Tango_ChangeEventProp_abs_change);

    u_octet4_loop_Tango_ChangeEventProp_extensions = get_CDR_ulong(tvb, offset, stream_is_big_endian, boundary);

    item = proto_tree_add_uint(tree, hf_Tango_ChangeEventProp_extensions_loop, tvb,*offset-4, 4, u_octet4_loop_Tango_ChangeEventProp_extensions);

    for (i_Tango_ChangeEventProp_extensions=0; i_Tango_ChangeEventProp_extensions < u_octet4_loop_Tango_ChangeEventProp_extensions; i_Tango_ChangeEventProp_extensions++) {

        giop_add_CDR_string(tree, tvb, offset, stream_is_big_endian, boundary, hf_Tango_ChangeEventProp_extensions);

    }

}
