acceptFile(const std::string &path)
{
    return !Path::isHeader(path) && (Path::isCPP(path) || Path::isC(path));
}
