getRawDigest()
{
    std::string result;
    switch (bits)
    {
      case 256:
        result = std::string(reinterpret_cast<char*>(this->sha256sum),
                             sizeof(this->sha256sum));
        break;
      case 384:
        result = std::string(reinterpret_cast<char*>(this->sha384sum),
                             sizeof(this->sha384sum));
        break;
      case 512:
        result = std::string(reinterpret_cast<char*>(this->sha512sum),
                             sizeof(this->sha512sum));
        break;
      default:
        badBits();
        break;
    }
    return result;
}
