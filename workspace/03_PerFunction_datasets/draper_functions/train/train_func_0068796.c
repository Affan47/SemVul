createPath(const std::string &file)
{
    std::string parent = dirPath(file);
    if (!FsPath::exists(parent)) {
        createPath(parent);
        createDir(parent);
    }
}
