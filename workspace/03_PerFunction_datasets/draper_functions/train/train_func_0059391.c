get_rest_of_line()
{

    Token t;
    t.type = kTokenRest;
    while (isspace(*cur_))
        ++cur_;
    t.str = peeked_ ? tok_.str : cur_;
    peeked_ = false;
    while (*cur_ != '\0')
        ++cur_;
    t.length = cur_ - t.str;
    return t;
}
