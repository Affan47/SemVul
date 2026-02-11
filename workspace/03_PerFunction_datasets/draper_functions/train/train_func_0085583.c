heim_error_get_code(heim_error_t error)
{
    if (heim_get_tid(error) != HEIM_TID_ERROR) {
	if (heim_get_tid(error) == heim_number_get_type_id())
	    return heim_number_get_int((heim_number_t)error);
	heim_abort("invalid heim_error_t");
    }
    return error->error_code;
}
