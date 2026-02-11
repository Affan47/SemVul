click_static_initialize()
{
    cp_va_static_initialize();
    ErrorHandler::static_initialize(new FileErrorHandler(stderr, ""));
    LandmarkT::static_initialize();
}
