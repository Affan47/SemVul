get_glob_token()
{
    if (peeked_) {

        cur_ = tok_.str;
        peeked_ = false;
    }
    read_token(true);
    return tok_;
}
