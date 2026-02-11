handleMineButtonDown(const CEGUI::EventArgs& event)
{
    const CEGUI::MouseEventArgs& me = static_cast<const CEGUI::MouseEventArgs&>(event);
    if (me.button == CEGUI::RightButton)
    {
        CEGUI::Window* button = me.window;
        if (!button->isDisabled())
        {
            if (button->getID() == 0)
            {
                button->setID(1);
                button->setText("F");
            }
            else
            {
                button->setID(0);
                button->setText("");
            }
            return true;
        }
    }
    return false;
}
