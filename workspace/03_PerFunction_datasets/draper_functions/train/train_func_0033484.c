libcec_read_message(libcec_device_handle* handle, uint8_t* buffer, size_t length, int32_t timeout)
{
	if ((handle == NULL) || (buffer == NULL) || (length == 0)) {
		return LIBCEC_ERROR_INVALID_PARAM;
	}
	return ceci_backend->read_message(handle, buffer, length, timeout);
}
