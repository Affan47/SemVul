Encrypt(std::string* dst, const std::string& src) const
{
    std::string padded_data = src;

    size_t padding_length = src.length() % sizeof(uint64_t);
    if (padding_length == 0)
        padding_length = sizeof(uint64_t);
    else
        padding_length = sizeof(uint64_t) - padding_length;
    for (size_t i = 0; i < padding_length; ++i) {
        padded_data += static_cast<char>(padding_length);
    }

    dst->resize(padded_data.size());
    Encrypt(&(*dst)[0], padded_data.data(), padded_data.size());
}
