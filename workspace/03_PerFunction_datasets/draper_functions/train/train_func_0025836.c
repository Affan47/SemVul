Rivet_SetScript (apr_pool_t *pool, rivet_server_conf *rsc, const char *script, const char *string)
{
    Tcl_Obj *objarg = NULL;

    if( STREQU( script, "GlobalInitScript" ) ) {
        objarg = Rivet_AssignStringToConf(&(rsc->rivet_global_init_script),string);
    } else if( STREQU( script, "ChildInitScript" ) ) {
        objarg = Rivet_AssignStringToConf(&(rsc->rivet_child_init_script),string);
    } else if( STREQU( script, "ChildExitScript" ) ) {
        objarg = Rivet_AssignStringToConf(&(rsc->rivet_child_exit_script),string);
    } else if( STREQU( script, "BeforeScript" ) ) {
        objarg = Rivet_AssignStringToConf(&(rsc->rivet_before_script),string);
    } else if( STREQU( script, "AfterScript" ) ) {
        objarg = Rivet_AssignStringToConf(&(rsc->rivet_after_script),string);
    } else if( STREQU( script, "ErrorScript" ) ) {
        objarg = Rivet_AssignStringToConf(&(rsc->rivet_error_script),string);
    } else if( STREQU( script, "ServerInitScript" ) ) {
        objarg = Rivet_AssignStringToConf(&(rsc->rivet_server_init_script),string);
    } else if( STREQU( script, "AbortScript" ) ) {
        objarg = Rivet_AssignStringToConf(&(rsc->rivet_abort_script),string);
    } else if( STREQU( script, "AfterEveryScript" ) ) {
        objarg = Rivet_AssignStringToConf(&(rsc->after_every_script),string);
    }

    if( !objarg ) return string;

    return Tcl_GetStringFromObj( objarg, NULL );
}
