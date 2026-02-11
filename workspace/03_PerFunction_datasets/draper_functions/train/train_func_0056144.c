_fiid_obj_packet_valid (fiid_obj_t obj, int makes_packet_sufficient_checks)
{
  unsigned int total_set_bits_counter = 0, max_bits_counter = 0,
    set_bits_counter = 0, optional_bits_counter = 0;
  unsigned int i;

  assert (obj);
  assert (obj->magic == FIID_OBJ_MAGIC);
  assert (!makes_packet_sufficient_checks || obj->makes_packet_sufficient);

  for (i = 0; i < obj->field_data_len; i++)
    {
      unsigned int required_flag = FIID_FIELD_REQUIRED_FLAG (obj->field_data[i].flags);
      unsigned int length_flag = FIID_FIELD_LENGTH_FLAG (obj->field_data[i].flags);
      unsigned int max_field_len = obj->field_data[i].max_field_len;
      unsigned int set_field_len = obj->field_data[i].set_field_len;
      unsigned int makes_packet_sufficient_flag = obj->field_data[i].flags & FIID_FIELD_MAKES_PACKET_SUFFICIENT;

      if (makes_packet_sufficient_checks)
        {

          if (makes_packet_sufficient_flag)
            {
              if (!set_field_len)
                return (0);

              if (length_flag == FIID_FIELD_LENGTH_FIXED && max_field_len != set_field_len)
                return (0);
            }
        }
      else
        {
          if (required_flag == FIID_FIELD_REQUIRED && !set_field_len)
            {
              obj->errnum = FIID_ERR_REQUIRED_FIELD_MISSING;
              return (0);
            }

          if ((length_flag == FIID_FIELD_LENGTH_FIXED && max_field_len != set_field_len)
              && (required_flag == FIID_FIELD_REQUIRED
                  || (required_flag == FIID_FIELD_OPTIONAL && set_field_len)))

            {
              obj->errnum = FIID_ERR_FIXED_LENGTH_FIELD_INVALID;
              return (0);
            }
        }

      max_bits_counter += max_field_len;
      total_set_bits_counter += set_field_len;

      if (set_field_len)
        {
          if (optional_bits_counter)
            {
              obj->errnum = FIID_ERR_DATA_NOT_BYTE_ALIGNED;
              return (0);
            }

          if (set_field_len != max_field_len)
            {


              if ((set_bits_counter + set_field_len) % 8)
                {
                  obj->errnum = FIID_ERR_DATA_NOT_BYTE_ALIGNED;
                  return (0);
                }
            }

          set_bits_counter += set_field_len;
          if (!(set_bits_counter % 8))
            {
              set_bits_counter = 0;
              max_bits_counter = 0;
            }
        }
      else
        {


          if (set_bits_counter)
            {
              obj->errnum = FIID_ERR_DATA_NOT_BYTE_ALIGNED;
              return (0);
            }


          optional_bits_counter += max_field_len;
          if (optional_bits_counter && !(optional_bits_counter % 8))
            {

              if (optional_bits_counter != max_bits_counter)
                {
                  obj->errnum = FIID_ERR_DATA_NOT_BYTE_ALIGNED;
                  return (0);
                }

              optional_bits_counter = 0;
              max_bits_counter = 0;
            }
        }
    }


  if (set_bits_counter)
    {
      obj->errnum = FIID_ERR_DATA_NOT_BYTE_ALIGNED;
      return (0);
    }


  if (total_set_bits_counter % 8)
    {
      obj->errnum = FIID_ERR_DATA_NOT_BYTE_ALIGNED;
      return (0);
    }

  obj->errnum = FIID_ERR_SUCCESS;
  return (1);
}
