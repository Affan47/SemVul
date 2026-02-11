ReadPicData (std::ifstream &fdata, unsigned char *buffer, int frame_size)
{
    bool ret_stat = true;

    ios::iostate oldExceptions = fdata.exceptions();
    fdata.exceptions (ios::failbit | ios::badbit);
    try
    {
        fdata.read ((char *)buffer, frame_size);
    }
    catch (...)
    {
        ret_stat = false;
    }
    fdata.exceptions (oldExceptions);
    return ret_stat;
}
