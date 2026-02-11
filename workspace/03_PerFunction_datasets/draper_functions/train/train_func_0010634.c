log4cplus_file_configure(const log4cplus_char_t *pathname)
{
    if( !pathname )
        return EINVAL;

    try
    {
        PropertyConfigurator::doConfigure( pathname );
    }
    catch(STD_NAMESPACE exception const &)
    {
        return -1;
    }

    return 0;
}
