tooManyConfigsError(const std::string &file, const std::size_t numberOfConfigurations)
{
    if (!_settings.isEnabled("information") && !tooManyConfigs)
        return;

    tooManyConfigs = false;

    if (_settings.isEnabled("information") && file.empty())
        return;

    std::list<ErrorLogger::ErrorMessage::FileLocation> loclist;
    if (!file.empty()) {
        ErrorLogger::ErrorMessage::FileLocation location;
        location.setfile(file);
        loclist.push_back(location);
    }

    std::ostringstream msg;
    msg << "Too many #ifdef configurations - cppcheck only checks " << _settings._maxConfigs;
    if (numberOfConfigurations > _settings._maxConfigs)
        msg << " of " << numberOfConfigurations << " configurations. Use --force to check all configurations.\n";
    if (file.empty())
        msg << " configurations. Use --force to check all configurations. For more details, use --enable=information.\n";
    msg << "The checking of the file will be interrupted because there are too many "
        "#ifdef configurations. Checking of all #ifdef configurations can be forced "
        "by --force command line option or from GUI preferences. However that may "
        "increase the checking time.";
    if (file.empty())
        msg << " For more details, use --enable=information.";


    ErrorLogger::ErrorMessage errmsg(loclist,
                                     Severity::information,
                                     msg.str(),
                                     "toomanyconfigs",
                                     false);

    reportErr(errmsg);
}
