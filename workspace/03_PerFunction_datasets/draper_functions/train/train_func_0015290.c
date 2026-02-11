externalinterface_uEscapeXML(const fn_call& fn)
{
    if (fn.nargs == 1) {
        std::string str(fn.arg(0).to_string());
        escapeXML(str);
        return as_value(str);
    }

    return as_value();
}
