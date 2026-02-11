stp_verify_parameter(const stp_vars_t *v, const char *parameter,
		     int quiet)
{
  stp_parameter_t desc;
  quiet = 0;
  stp_describe_parameter(v, parameter, &desc);
  stp_dprintf(STP_DBG_VARS, v, "  Verifying %s %d %d\n", parameter,
	      desc.is_active, desc.read_only);
  if (!desc.is_active || desc.read_only)
    {
      stp_parameter_description_destroy(&desc);
      return PARAMETER_INACTIVE;
    }
  switch (desc.p_type)
    {
    case STP_PARAMETER_TYPE_STRING_LIST:
      return verify_string_param(v, parameter, &desc, quiet);
    case STP_PARAMETER_TYPE_DOUBLE:
      return verify_double_param(v, parameter, &desc, quiet);
    case STP_PARAMETER_TYPE_INT:
      return verify_int_param(v, parameter, &desc, quiet);
    case STP_PARAMETER_TYPE_DIMENSION:
      return verify_dimension_param(v, parameter, &desc, quiet);
    case STP_PARAMETER_TYPE_CURVE:
      return verify_curve_param(v, parameter, &desc, quiet);
    case STP_PARAMETER_TYPE_RAW:
    case STP_PARAMETER_TYPE_FILE:
      stp_parameter_description_destroy(&desc);
      return PARAMETER_OK;
    case STP_PARAMETER_TYPE_BOOLEAN:
      stp_parameter_description_destroy(&desc);
      return PARAMETER_OK;
    default:
      if (!quiet)
	stp_eprintf(v, _("Unknown type parameter %s (%d)\n"),
		    parameter, desc.p_type);
      stp_parameter_description_destroy(&desc);
      return 0;
    }
}
