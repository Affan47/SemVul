GetErrorString(SquirrelError* exception, bool clearErrors)
{
    wxString msg;
    if (exception)
        msg << cbC2U(exception->desc);
    msg << s_ScriptErrors;

    if (clearErrors)
        s_ScriptErrors.Clear();

    return msg;
}
