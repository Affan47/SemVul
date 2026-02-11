ValidateVersion(void) {

    const string& version = m_header.Version;


    if ( version.empty() ) {
        AddWarning("Version (VN) missing. Not required, but strongly recommended");
        return true;
    }


    const size_t periodFound = version.find(Constants::SAM_PERIOD);
    if ( periodFound == string::npos ) {
        AddError("Invalid version (VN) format: " + version);
        return false;
    }


    const string majorVersion = version.substr(0, periodFound);
    if ( majorVersion.empty() || !ContainsOnlyDigits(majorVersion) ) {
        AddError("Invalid version (VN) format: " + version);
        return false;
    }


    const string minorVersion = version.substr(periodFound + 1);
    if ( minorVersion.empty() || !ContainsOnlyDigits(minorVersion) ) {
        AddError("Invalid version (VN) format: " + version);
        return false;
    }


    return true;
}
