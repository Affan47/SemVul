SetHeaderText(const std::string& headerText) {


    Clear();


    SamFormatParser parser(*this);
    parser.Parse(headerText);
}
