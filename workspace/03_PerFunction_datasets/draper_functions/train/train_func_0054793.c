getFilesize(const std::string& filename)
{
    std::ifstream in(filename.c_str(), std::ifstream::in | std::ifstream::binary);
    in.seekg(0, std::ifstream::end);
    return in.tellg();
}
