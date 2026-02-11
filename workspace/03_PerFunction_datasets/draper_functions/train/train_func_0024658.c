setURL(std::string url)
{
    if (_url != url) {
        set_invalidated();
        _url = url;
    }
}
