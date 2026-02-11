Scm_SetInputPort(ScmObj port)
{
    if ((!SCM_PORTP(port))) {
        Scm_Error("<port> required, but got %S", port);
    }

    input_port = port;

    line_buffer = first_line_buffer;
    line_number = 0;
    line_position = 0;

    SCM_RETURN(SCM_UNDEFINED);
}
