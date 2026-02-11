on_run_output (AnjutaLauncher* launcher, AnjutaLauncherOutputType type,
			   const gchar* output, gpointer user_data)
{
	ATPExecutionContext* this = (ATPExecutionContext*)user_data;

	switch (type)
	{
	case ANJUTA_LAUNCHER_OUTPUT_STDOUT:
		atp_output_context_print (&this->output, output);
		break;
	case ANJUTA_LAUNCHER_OUTPUT_STDERR:
		atp_output_context_print (&this->error, output);
		break;
	case ANJUTA_LAUNCHER_OUTPUT_PTY:
		break;
	}
}
