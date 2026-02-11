doGet(const void* target) const
    {
        const BorderPanelOverlayElement* t = static_cast<const BorderPanelOverlayElement*>(target);
        return String(
            StringConverter::toString(t->getLeftBorderSize()) + " " +
            StringConverter::toString(t->getRightBorderSize()) + " " +
            StringConverter::toString(t->getTopBorderSize()) + " " +
            StringConverter::toString(t->getBottomBorderSize()) );
    }
