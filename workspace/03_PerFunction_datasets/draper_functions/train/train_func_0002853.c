ne_version_match(int major, int minor)
{
    return NE_VERSION_MAJOR != major || NE_VERSION_MINOR < minor
        || (NE_VERSION_MAJOR == 0 && NE_VERSION_MINOR != minor);
}
