handleFocusOut()
{
    TextAreaWidget* w = static_cast<TextAreaWidget*>(m_widget);

    if ( w && element()->m_changed ) {
        element()->m_changed = false;
        element()->onChange();
    }
}
