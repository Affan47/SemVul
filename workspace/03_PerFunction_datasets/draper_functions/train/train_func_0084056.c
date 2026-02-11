mouseDrive(const InputProvider *input) const
{
    bool moved = false;
    V2 field = m_view->getFieldPos(input->getMouseLoc());
    if (input->isLeftPressed()) {
        moved = moveTo(field);
    }
    else if (input->isRightPressed()) {
        moved = moveHardTo(field);
    }
    return moved;
}
