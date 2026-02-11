Close()
{
    Flush();

    if (doc)
        delete doc;

    doc = nullptr;
}
