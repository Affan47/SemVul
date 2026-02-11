removeItem(const string &uid)
{
    string filename = createFilename(uid);

    if (unlink(filename.c_str())) {
        throwError(filename, errno);
    }
}
