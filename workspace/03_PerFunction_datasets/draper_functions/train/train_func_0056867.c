getClientChildWindowContentArea_impl() const
{
    if (!d_parent)
        return Window::getClientChildWindowContentArea_impl();
    else
        return Rect(getUnclippedOuterRect().getPosition(),
                    d_parent->getUnclippedInnerRect().getSize());
}
