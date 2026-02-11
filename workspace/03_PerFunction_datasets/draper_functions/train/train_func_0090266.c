ShortFilename() const
{
    return Filename().substr(0, Filename().find_last_of("."));
}
