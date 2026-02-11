get_expected_token(const string& raw1, const string& raw2)
{
    TokenType p = peek_token().type;
    string s = peek_token().as_string();
    if (s != raw1 && s != raw2) {
        string msg = "expected `" + raw1 + "' or `" + raw2 + "'";
        throw_syntax_error(p == kTokenNop ? msg
                                          : msg + " instead of `" + s + "'");
    }
    return get_token();
}
