mono_error_set_argument (MonoError *oerror, const char *argument, const char *msg_format, ...)
{
	MonoErrorInternal *error = (MonoErrorInternal*)oerror;
	mono_error_prepare (error);

	error->error_code = MONO_ERROR_ARGUMENT;
	error->type_name = argument;

	set_error_message ();
}
