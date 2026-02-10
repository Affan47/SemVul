choiceType() const
{
  FormWidgetChoice* fwc = static_cast<FormWidgetChoice*>(m_formData->fm);
  if (fwc->isCombo())
    return FormFieldChoice::ComboBox;
  return FormFieldChoice::ListBox;
}
