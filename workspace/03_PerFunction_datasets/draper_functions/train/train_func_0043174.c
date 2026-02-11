realtek_cec_write_message(libcec_device_handle* handle, uint8_t* buffer, size_t length)
{
	realtek_device_handle_priv* handle_priv = __device_handle_priv(handle);
	int ret_val;
	cec_msg msg;

	if (length > 255) {
		return LIBCEC_ERROR_INVALID_PARAM;
	}
	msg.buf = buffer;
	msg.len = (unsigned char)length;

	ret_val = ioctl(handle_priv->cec_dev, CEC_SEND_MESSAGE, &msg);
	if (ret_val) {
		ceci_error("failed to send CEC message - errno: %d");
		return LIBCEC_ERROR_IO;
	}
	return LIBCEC_SUCCESS;
}
