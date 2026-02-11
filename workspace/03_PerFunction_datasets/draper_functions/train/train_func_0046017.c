setUpPoller()
{
    if (!isAvailable()) {
        return false;
    }

    kDebug() << "XSync Inited";

    KApplication::kApplication()->installX11EventFilter(this);

    kDebug() << "Supported, init completed";

    return true;
}
