decode_Tango_Device_read_attributes(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, proto_item *item _U_, int *offset _U_, MessageHeader *header, const gchar *operation _U_, gboolean stream_is_big_endian _U_)
{

    guint32   u_octet4_loop_Tango_Device_read_attributes_names;
    guint32   i_Tango_Device_read_attributes_names;
    guint32   u_octet4_loop_Tango_Device_read_attributes_return;
    guint32   i_Tango_Device_read_attributes_return;


    (void)item;

    switch(header->message_type) {
    case Request:
        u_octet4_loop_Tango_Device_read_attributes_names = get_CDR_ulong(tvb, offset, stream_is_big_endian, boundary);

        item = proto_tree_add_uint(tree, hf_Tango_Device_read_attributes_names_loop, tvb,*offset-4, 4, u_octet4_loop_Tango_Device_read_attributes_names);

        for (i_Tango_Device_read_attributes_names=0; i_Tango_Device_read_attributes_names < u_octet4_loop_Tango_Device_read_attributes_names; i_Tango_Device_read_attributes_names++) {

            giop_add_CDR_string(tree, tvb, offset, stream_is_big_endian, boundary, hf_Tango_Device_read_attributes_names);

        }

        break;
    case Reply:
        switch(header->rep_status) {
        case NO_EXCEPTION:
            u_octet4_loop_Tango_Device_read_attributes_return = get_CDR_ulong(tvb, offset, stream_is_big_endian, boundary);

            item = proto_tree_add_uint(tree, hf_Tango_Device_read_attributes_return_loop, tvb,*offset-4, 4, u_octet4_loop_Tango_Device_read_attributes_return);

            for (i_Tango_Device_read_attributes_return=0; i_Tango_Device_read_attributes_return < u_octet4_loop_Tango_Device_read_attributes_return; i_Tango_Device_read_attributes_return++) {


                decode_Tango_AttributeValue_st(tvb, pinfo, tree, item, offset, header, operation, stream_is_big_endian);

            }

            break;
        case USER_EXCEPTION:
            break;
        default:

            expert_add_info_format(pinfo, item, &ei_tango_unknown_exception, "Unknown exception %d", header->rep_status);
            break;
        }

        break;
    default:

        expert_add_info_format(pinfo, item, &ei_tango_unknown_giop_msg, "Unknown GIOP message %d", header->message_type);
        break;
    }
}
