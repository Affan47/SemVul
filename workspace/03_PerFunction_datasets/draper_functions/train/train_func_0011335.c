setWriteDisk(bool use)
{
    if (!use) closeLog();
    _write = use;
}
