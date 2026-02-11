scm_dynwind_current_output_port (SCM port)
#define FUNC_NAME NULL
{
  port = SCM_COERCE_OUTPORT (port);
  SCM_VALIDATE_OPOUTPORT (1, port);
  scm_dynwind_fluid (cur_outport_fluid, port);
}
