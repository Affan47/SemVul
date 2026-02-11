OnPreview(wxCommandEvent & WXUNUSED(event))
{
   TransferDataFromWindow();


   double oldSemitonesChange = m_dSemitonesChange;
   if( m_dPercentChange < PERCENTCHANGE_MIN)
   {
      m_dPercentChange = PERCENTCHANGE_MIN;
      this->Update_Text_PercentChange();
   }
   mEffect->m_dSemitonesChange = m_dSemitonesChange;
   mEffect->Preview();
   mEffect->m_dSemitonesChange = oldSemitonesChange;
}
