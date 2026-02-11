fatalAssert(bool shouldBeTrue, const char* error)
{
    if (!shouldBeTrue)
        kFatal() << error;
}
