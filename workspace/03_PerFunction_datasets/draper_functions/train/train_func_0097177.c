OnText_SemitonesChange(wxCommandEvent & WXUNUSED(event))
{
   if (m_bLoopDetect)
      return;

   if (m_pTextCtrl_SemitonesChange) {
      wxString str = m_pTextCtrl_SemitonesChange->GetValue();
      if (str.IsEmpty())
         m_dSemitonesChange = 0.0;
      else
      {
         double newValue = 0;
         str.ToDouble(&newValue);
         m_dSemitonesChange = newValue;
      }

      this->Calc_PercentChange();
      this->Calc_ToFrequency();
      this->Calc_ToPitch();
      this->Calc_ToOctave();

      m_bLoopDetect = true;
      {
         this->Update_Choice_ToPitch();
         this->Update_Spin_ToOctave();
         this->Update_Text_ToFrequency();
         this->Update_Text_PercentChange();
         this->Update_Slider_PercentChange();
      }
      m_bLoopDetect = false;


      bool bIsGoodValue = (m_dSemitonesChange > -80.0) && (m_dSemitonesChange <= 60.0);
      this->FindWindow(wxID_OK)->Enable(bIsGoodValue);
      this->FindWindow(ID_EFFECT_PREVIEW)->Enable(bIsGoodValue);
   }
}
