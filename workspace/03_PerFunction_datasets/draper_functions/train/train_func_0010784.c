onZChange_impl(void)
{
    if (!d_parent)
    {
        WindowEventArgs args(this);
        onZChanged(args);
    }
    else
    {
        const size_t child_count = d_parent->getChildCount();

        for (size_t i = 0; i < child_count; ++i)
        {
            WindowEventArgs args(d_parent->d_children[i]);
            d_parent->d_children[i]->onZChanged(args);
        }

    }

    System::getSingleton().updateWindowContainingMouse();
}
