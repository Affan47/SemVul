OnSlider_PercentChange(wxCommandEvent & WXUNUSED(event))
{
   if (m_bLoopDetect)
      return;

   if (m_pSlider_PercentChange) {
      m_PercentChange = (double)(m_pSlider_PercentChange->GetValue());

      if (m_PercentChange > 0.0)
         m_PercentChange = pow(m_PercentChange, PERCENTCHANGE_SLIDER_WARP);

      m_bLoopDetect = true;
      this->Update_Text_PercentChange();
      this->Update_Text_ToBPM();
      this->Update_Text_ToLength();
      m_bLoopDetect = false;
   }
}
