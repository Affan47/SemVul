onKeyDown(KeyEventArgs& e)
{
    ScrolledItemListBase::onKeyDown(e);


    if (d_multiSelect)
    {
        uint sysKeys = System::getSingletonPtr()->getSystemKeys();
        if (e.scancode == Key::A && (sysKeys&Control))
        {
            selectAllItems();
            ++e.handled;
        }
    }
}
