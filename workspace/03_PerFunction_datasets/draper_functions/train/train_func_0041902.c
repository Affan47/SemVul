P_Display_Protocol_Version (Object d) {
    Check_Type (d, T_Display);
    return Cons (Make_Integer (ProtocolVersion (DISPLAY(d)->dpy)),
        Make_Integer (ProtocolRevision (DISPLAY(d)->dpy)));
}
