fill_sol_payload_data (uint8_t packet_sequence_number,
                       uint8_t packet_ack_nack_sequence_number,
                       uint8_t accepted_character_count,
                       uint8_t operation_status,
                       const void *character_data,
                       unsigned int character_data_len,
                       fiid_obj_t obj_sol_payload)
{
  if (!fiid_obj_valid (obj_sol_payload))
    {
      SET_ERRNO (EINVAL);
      return (-1);
    }

  if (FIID_OBJ_TEMPLATE_COMPARE (obj_sol_payload, tmpl_sol_payload_data) < 0)
    {
      ERRNO_TRACE (errno);
      return (-1);
    }

  FILL_FIID_OBJ_CLEAR (obj_sol_payload);
  FILL_FIID_OBJ_SET (obj_sol_payload, "packet_sequence_number", packet_sequence_number);
  FILL_FIID_OBJ_SET (obj_sol_payload, "reserved1", 0);
  FILL_FIID_OBJ_SET (obj_sol_payload, "packet_ack_nack_sequence_number", packet_ack_nack_sequence_number);
  FILL_FIID_OBJ_SET (obj_sol_payload, "reserved2", 0);
  FILL_FIID_OBJ_SET (obj_sol_payload, "accepted_character_count", accepted_character_count);
  FILL_FIID_OBJ_SET (obj_sol_payload, "operation_status", operation_status);
  if (character_data && character_data_len)
    FILL_FIID_OBJ_SET_DATA (obj_sol_payload,
                            "character_data",
                            character_data,
                            character_data_len);

  return (0);
}
