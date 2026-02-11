SetValue(bool depressed)
{
  wxCHECK_RET(!(m_button_style & wxCUSTBUT_NOTOGGLE), wxT("can't set button state"));
    m_down = depressed ? 1 : 0;
    Refresh(false);
}
