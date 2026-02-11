setVisible(bool visible)
{
    if (d_ptr->isVisible != visible) {
        d_ptr->isVisible = visible;
        emit visibleChanged(d_ptr->isVisible);
    }
}
