cam_set_current( camera_t *camera )
{
    static char str[200];

    Tcl_SetVar2( TCLInterp, "camera","name", camera->Name, TCL_GLOBAL_ONLY );

    Tcl_SetVar2( TCLInterp, "camera","display", "on", TCL_GLOBAL_ONLY );

    if ( camera->ProjectionType == camera_proj_ortho )
        Tcl_SetVar2( TCLInterp, "camera","projection", "ortho",TCL_GLOBAL_ONLY );
    else
        Tcl_SetVar2( TCLInterp, "camera","projection", "perspective",TCL_GLOBAL_ONLY );

    sprintf( str, "%g", camera->LookFromX );
    Tcl_SetVar2( TCLInterp, "camera","from_x", str, TCL_GLOBAL_ONLY );

    sprintf( str, "%g", camera->LookFromY );
    Tcl_SetVar2( TCLInterp, "camera","from_y", str, TCL_GLOBAL_ONLY );

    sprintf( str, "%g", camera->LookFromZ );
    Tcl_SetVar2( TCLInterp, "camera","from_z", str, TCL_GLOBAL_ONLY );

    sprintf( str, "%g", camera->LookAtX );
    Tcl_SetVar2( TCLInterp, "camera","to_x", str, TCL_GLOBAL_ONLY );

    sprintf( str, "%g", camera->LookAtY );
    Tcl_SetVar2( TCLInterp, "camera", "to_y", str, TCL_GLOBAL_ONLY );

    sprintf( str, "%g", camera->LookAtZ );
    Tcl_SetVar2( TCLInterp, "camera","to_z", str, TCL_GLOBAL_ONLY );

    sprintf( str, "%g", camera->UpX );
    Tcl_SetVar2( TCLInterp, "camera","up_x", str, TCL_GLOBAL_ONLY );

    sprintf( str, "%g", camera->UpY );
    Tcl_SetVar2( TCLInterp, "camera","up_y", str, TCL_GLOBAL_ONLY );

    sprintf( str, "%g", camera->UpZ );
    Tcl_SetVar2( TCLInterp, "camera","up_z", str, TCL_GLOBAL_ONLY );

    sprintf( str, "%g", camera->FieldAngle );
    Tcl_SetVar2( TCLInterp, "camera","field_angle", str, TCL_GLOBAL_ONLY );

    sprintf( str, "%g", camera->ClipNear );
    Tcl_SetVar2( TCLInterp, "camera","near", str, TCL_GLOBAL_ONLY );

    sprintf( str, "%g", camera->ClipFar );
    Tcl_SetVar2( TCLInterp, "camera","far", str, TCL_GLOBAL_ONLY );

    sprintf( str, "%g", camera->ViewportLowX );
    Tcl_SetVar2( TCLInterp, "camera","view_low_x", str, TCL_GLOBAL_ONLY );

    sprintf( str, "%g", camera->ViewportLowY );
    Tcl_SetVar2( TCLInterp, "camera","view_low_y", str, TCL_GLOBAL_ONLY );

    sprintf( str, "%g", camera->ViewportHighX );
    Tcl_SetVar2( TCLInterp, "camera","view_high_x", str, TCL_GLOBAL_ONLY );

    sprintf( str, "%g", camera->ViewportHighY );
    Tcl_SetVar2( TCLInterp, "camera","view_high_y", str, TCL_GLOBAL_ONLY );
}
