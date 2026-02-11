cbf_set_axis_setting (cbf_handle handle, unsigned int  reserved,
                                             const char   *axis_id,
                                             double        start,
                                             double        increment)
{
  cbf_axis_type type;

  if (reserved != 0)

    return CBF_ARGUMENT;


  cbf_failnez (cbf_get_axis_type (handle, axis_id, &type))

  if (type != CBF_TRANSLATION_AXIS && type != CBF_ROTATION_AXIS)

    return CBF_FORMAT;


  if (type == CBF_TRANSLATION_AXIS)
  {
    cbf_failnez (cbf_require_category   (handle, "diffrn_scan_frame_axis"))
    cbf_failnez (cbf_require_column     (handle, "axis_id"))
    cbf_failnez (cbf_require_row        (handle, axis_id))
    cbf_failnez (cbf_require_column     (handle, "displacement"))
    cbf_failnez (cbf_set_doublevalue    (handle, "%-.15g", start))
    if (!cbf_find_column( handle, "displacement_increment")) {
      cbf_failnez (cbf_set_doublevalue    (handle, "%-.15g", increment))
    }

    cbf_failnez (cbf_require_category   (handle, "diffrn_scan_axis"))
    cbf_failnez (cbf_require_column     (handle, "axis_id"))
    cbf_failnez (cbf_require_row        (handle, axis_id))
    cbf_failnez (cbf_require_column     (handle, "displacement_start"))
    cbf_failnez (cbf_set_doublevalue    (handle, "%-.15g", start))
    cbf_failnez (cbf_require_column     (handle, "displacement_increment"))
    cbf_failnez (cbf_set_doublevalue    (handle, "%-.15g", increment))
    cbf_failnez (cbf_require_column     (handle, "displacement_range"))
    cbf_failnez (cbf_set_doublevalue    (handle, "%-.15g", increment))
  }
  else
  {
    cbf_failnez (cbf_require_category   (handle, "diffrn_scan_frame_axis"))
    cbf_failnez (cbf_require_column     (handle, "axis_id"))
    cbf_failnez (cbf_require_row        (handle, axis_id))
    cbf_failnez (cbf_require_column     (handle, "angle"))
    cbf_failnez (cbf_set_doublevalue    (handle, "%-.15g", start))
    if (!cbf_find_column     (handle, "angle_increment")) {
      cbf_failnez (cbf_set_doublevalue    (handle, "%-.15g", increment))
    }
    cbf_failnez (cbf_require_category   (handle, "diffrn_scan_axis"))
    cbf_failnez (cbf_require_column     (handle, "axis_id"))
    cbf_failnez (cbf_require_row        (handle, axis_id))
    cbf_failnez (cbf_require_column     (handle, "angle_start"))
    cbf_failnez (cbf_set_doublevalue    (handle, "%-.15g", start))
    cbf_failnez (cbf_require_column     (handle, "angle_increment"))
    cbf_failnez (cbf_set_doublevalue    (handle, "%-.15g", increment))
    cbf_failnez (cbf_require_column     (handle, "angle_range"))
    cbf_failnez (cbf_set_doublevalue    (handle, "%-.15g", increment))
  }

  return 0;
}
