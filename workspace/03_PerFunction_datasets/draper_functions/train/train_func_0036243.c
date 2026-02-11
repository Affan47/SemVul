setIndeterminate(bool _indeterminate)
{

    if (inputType() != CHECKBOX || inputType() != RADIO || indeterminate() == _indeterminate)
        return;

    m_indeterminate = _indeterminate;


    if (!changed() && m_render) {
        m_render->updateFromElement();
    }
}
