deflate(std::vector<unsigned char> &dest,
                       const std::vector<unsigned char> &src)
{
    reset();
    uncompressed = src;
    if (!compress())
        return false;
    dest = compressed;
    return true;
}
