globus_l_gsi_gss_assist_activate(void)
{
    int                                 result;
    char *                              tmp_string;
    static char *                       _function_name_ =
        "globus_l_gsi_gss_assist_activate";

    tmp_string = getenv("GLOBUS_GSI_GSS_ASSIST_DEBUG_LEVEL");
    if(tmp_string != GLOBUS_NULL)
    {
        globus_i_gsi_gss_assist_debug_level = atoi(tmp_string);
        if(globus_i_gsi_gss_assist_debug_level < 0)
        {
            globus_i_gsi_gss_assist_debug_level = 0;
        }
    }

    tmp_string = getenv("GLOBUS_GSI_GSS_ASSIST_DEBUG_FILE");
    if(tmp_string != GLOBUS_NULL)
    {
        globus_i_gsi_gss_assist_debug_fstream = fopen(tmp_string, "w");
        if(globus_i_gsi_gss_assist_debug_fstream == NULL)
        {
            result = GLOBUS_NULL;
            goto exit;
        }
    }
    else
    {
        globus_i_gsi_gss_assist_debug_fstream = stderr;
    }

    GLOBUS_I_GSI_GSS_ASSIST_DEBUG_ENTER;

    globus_module_activate(GLOBUS_COMMON_MODULE);
    globus_module_activate(GLOBUS_CALLOUT_MODULE);
    globus_module_activate(GLOBUS_GSI_SYSCONFIG_MODULE);
    globus_module_activate(GLOBUS_GSI_GSSAPI_MODULE);

    globus_mutex_init(&globus_i_gsi_gss_assist_mutex, NULL);

 exit:
    GLOBUS_I_GSI_GSS_ASSIST_DEBUG_EXIT;
    return GLOBUS_SUCCESS;
}
