ndmp_connection_err_msg(
    NDMPConnection *self)
{
    if (self->startup_err) {
	return g_strdup(self->startup_err);
    } else if (self->last_rc == NDMCONN_CALL_STATUS_REPLY_ERROR) {
	return g_strdup_printf("Error from NDMP server: %s",
		    ndmp9_error_to_str(self->conn->last_reply_error));
    } else if (self->last_rc) {
	return g_strdup_printf("ndmconn error %d: %s",
		    self->last_rc, ndmconn_get_err_msg(self->conn));
    } else {
	return g_strdup_printf("No error");
    }
}
