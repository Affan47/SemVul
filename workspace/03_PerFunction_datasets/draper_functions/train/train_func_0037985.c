getToken(const int index) const
{
    std::stringstream pastStringStream(context_tracker_callback->get_past_stream());
    ReverseTokenizer tokenizer(pastStringStream, blankspaceChars, separatorChars);
    tokenizer.lowercaseMode(lowercase_mode);

    std::string token;
    int i = 0;
    while (tokenizer.hasMoreTokens() && i <= index) {
        token = tokenizer.nextToken();
        i++;
    }
    if (i <= index) {

	token = "";
    }
    return token;


}
