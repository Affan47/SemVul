Validate(bool verbose) {


    bool isValid = true;
    isValid &= ValidateMetadata();
    isValid &= ValidateSequenceDictionary();
    isValid &= ValidateReadGroupDictionary();
    isValid &= ValidateProgramData();


    if ( verbose ) {
        PrintErrorMessages();
        PrintWarningMessages();
    }


    return isValid;
}
