onEnabled(WindowEventArgs& e)
{


    const size_t child_count = getChildCount();
    for (size_t i = 0; i < child_count; ++i)
    {
        if (d_children[i]->d_enabled)
        {
            WindowEventArgs args(d_children[i]);
            d_children[i]->onEnabled(args);
        }
    }

    invalidate();
    fireEvent(EventEnabled, e, EventNamespace);
}
