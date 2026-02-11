isCheckboxSelected(const CEGUI::String& checkbox)
{
    WindowManager& winMgr = WindowManager::getSingleton();

    if (winMgr.isWindowPresent(checkbox))
    {
        Checkbox* button = static_cast<Checkbox*>(winMgr.getWindow(checkbox));
        return button->isSelected();
    }
    return false;
}
