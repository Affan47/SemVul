setfile(const std::string &file)
{
    _file = file;
    _file = Path::fromNativeSeparators(_file);
}
