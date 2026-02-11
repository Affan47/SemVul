run()
{
    try
    {
        RunListener();
    }
    catch (LastFmException& e)
    {
        emit exceptionThrown(e.tr_what());
    }
}
