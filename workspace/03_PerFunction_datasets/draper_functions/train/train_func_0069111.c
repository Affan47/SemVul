onMouseButtonUp(MouseEventArgs& e)
{

    if (d_autoRepeat && d_repeatButton != NoButton)
    {
        releaseInput();
        d_repeatButton = NoButton;
    }

    fireEvent(EventMouseButtonUp, e, EventNamespace);


    if (!e.handled && d_propagateMouseInputs &&
        d_parent && this != System::getSingleton().getModalTarget())
    {
        e.window = d_parent;
        d_parent->onMouseButtonUp(e);

        return;
    }


    ++e.handled;
}
