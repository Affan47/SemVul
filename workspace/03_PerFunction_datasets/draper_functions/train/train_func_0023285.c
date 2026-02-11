_sensor_reading_corner_case_checks (ipmi_sensor_read_ctx_t ctx,
                                    fiid_obj_t obj_cmd_rs)
{
  assert (ctx);
  assert (ctx->magic == IPMI_SENSOR_READ_CTX_MAGIC);
  assert (obj_cmd_rs);

  if (ipmi_check_completion_code (obj_cmd_rs,
                                  IPMI_COMP_CODE_NODE_BUSY) == 1)
    {
      SENSOR_READ_SET_ERRNUM (ctx, IPMI_SENSOR_READ_ERR_NODE_BUSY);
      return (-1);
    }


  else if ((ipmi_check_completion_code (obj_cmd_rs,
                                        IPMI_COMP_CODE_REQUESTED_SENSOR_DATA_OR_RECORD_NOT_PRESENT) == 1)
	   || (ipmi_check_completion_code (obj_cmd_rs,
					   IPMI_COMP_CODE_COMMAND_ILLEGAL_FOR_SENSOR_OR_RECORD_TYPE) == 1)
           || (ipmi_check_completion_code (obj_cmd_rs,
                                           IPMI_COMP_CODE_PARAMETER_OUT_OF_RANGE) == 1)
           || (ipmi_check_completion_code (obj_cmd_rs,
                                           IPMI_COMP_CODE_INVALID_DATA_FIELD_IN_REQUEST) == 1)
	   || (ipmi_check_completion_code (obj_cmd_rs,
					   IPMI_COMP_CODE_COMMAND_RESPONSE_COULD_NOT_BE_PROVIDED) == 1)
	   || (ipmi_check_completion_code (obj_cmd_rs,
                                           IPMI_COMP_CODE_REQUEST_PARAMETER_NOT_SUPPORTED) == 1)
	   || (ipmi_check_completion_code (obj_cmd_rs,
					   IPMI_COMP_CODE_DESTINATION_UNAVAILABLE) == 1))
    {
      SENSOR_READ_SET_ERRNUM (ctx, IPMI_SENSOR_READ_ERR_SENSOR_READING_UNAVAILABLE);
      return (-1);
    }
  else if ((ipmi_check_completion_code (obj_cmd_rs,
					IPMI_COMP_CODE_UNSPECIFIED_ERROR) == 1))
    {
      uint64_t val;
      int flag;


      if ((flag = fiid_obj_get (obj_cmd_rs,
				"reading_state",
				&val)) < 0)
	{
	  SENSOR_READ_FIID_OBJECT_ERROR_TO_SENSOR_READ_ERRNUM (ctx, obj_cmd_rs);
	  return (-1);
	}

      if (flag && val == IPMI_SENSOR_READING_STATE_UNAVAILABLE)
	{
	  SENSOR_READ_SET_ERRNUM (ctx, IPMI_SENSOR_READ_ERR_SENSOR_READING_UNAVAILABLE);
	  return (-1);
	}

      if (!(ctx->flags & IPMI_SENSOR_READ_FLAGS_IGNORE_SCANNING_DISABLED))
	{
	  if ((flag = fiid_obj_get (obj_cmd_rs,
				    "sensor_scanning",
				    &val)) < 0)
	    {
	      SENSOR_READ_FIID_OBJECT_ERROR_TO_SENSOR_READ_ERRNUM (ctx, obj_cmd_rs);
	      return (-1);
	    }

	  if (flag && val == IPMI_SENSOR_SCANNING_ON_THIS_SENSOR_DISABLE)
	    {
	      SENSOR_READ_SET_ERRNUM (ctx, IPMI_SENSOR_READ_ERR_SENSOR_SCANNING_DISABLED);
	      return (-1);
	    }
	}


    }

  return (0);
}
