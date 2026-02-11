ErrorStr(OM_uint32 majstat, OM_uint32 ) {
    std::string errstr;
    if(majstat & GSS_S_BAD_MECH) errstr+=":GSS_S_BAD_MECH";
    if(majstat & GSS_S_BAD_NAME) errstr+=":GSS_S_BAD_NAME";
    if(majstat & GSS_S_BAD_NAMETYPE) errstr+=":GSS_S_BAD_NAMETYPE";
    if(majstat & GSS_S_BAD_BINDINGS) errstr+=":GSS_S_BAD_BINDINGS";
    if(majstat & GSS_S_BAD_STATUS) errstr+=":GSS_S_BAD_STATUS";
    if(majstat & GSS_S_BAD_SIG) errstr+=":GSS_S_BAD_SIG";
    if(majstat & GSS_S_NO_CRED) errstr+=":GSS_S_NO_CRED";
    if(majstat & GSS_S_NO_CONTEXT) errstr+=":GSS_S_NO_CONTEXT";
    if(majstat & GSS_S_DEFECTIVE_TOKEN) errstr+=":GSS_S_DEFECTIVE_TOKEN";
    if(majstat & GSS_S_DEFECTIVE_CREDENTIAL) errstr+=":GSS_S_DEFECTIVE_CREDENTIAL";
    if(majstat & GSS_S_CREDENTIALS_EXPIRED) errstr+=":GSS_S_CREDENTIALS_EXPIRED";
    if(majstat & GSS_S_CONTEXT_EXPIRED) errstr+=":GSS_S_CONTEXT_EXPIRED";
    if(majstat & GSS_S_FAILURE) errstr+=":GSS_S_FAILURE";
    if(majstat & GSS_S_BAD_QOP) errstr+=":GSS_S_BAD_QOP";
    if(majstat & GSS_S_UNAUTHORIZED) errstr+=":GSS_S_UNAUTHORIZED";
    if(majstat & GSS_S_UNAVAILABLE) errstr+=":GSS_S_UNAVAILABLE";
    if(majstat & GSS_S_DUPLICATE_ELEMENT) errstr+=":GSS_S_DUPLICATE_ELEMENT";
    if(majstat & GSS_S_NAME_NOT_MN) errstr+=":GSS_S_NAME_NOT_MN";
    if(majstat & GSS_S_EXT_COMPAT) errstr+=":GSS_S_EXT_COMPAT";
    return errstr;
  }
}
