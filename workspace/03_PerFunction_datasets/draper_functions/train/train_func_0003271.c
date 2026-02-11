log4cplus_basic_configure(void)
{
    try
    {
        BasicConfigurator::doConfigure();
    }
    catch(STD_NAMESPACE exception const &)
    {
        return -1;
    }

    return 0;
}
