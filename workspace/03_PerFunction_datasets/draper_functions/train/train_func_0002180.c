irmo_connection_error(IrmoConnection *conn, char *s, ...)
{
	va_list args;

	if (conn->connection_error != NULL) {
		free(conn->connection_error);
        }

	va_start(args, s);

	conn->connection_error = irmo_vasprintf(s, args);

	va_end(args);
}
