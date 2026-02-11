OnSpin_ToOctave(wxCommandEvent & WXUNUSED(event))
{
   if (m_bLoopDetect)
      return;

   if (m_pSpin_ToOctave)
   {
      int nNewValue = m_pSpin_ToOctave->GetValue();


      if ((nNewValue + 3) < m_nFromOctave)
      {
         ::wxBell();
         m_pSpin_ToOctave->SetValue(m_nFromOctave - 3);
         return;
      }
      m_nToOctave = nNewValue;

      m_ToFrequency = PitchToFreq(m_nToPitch, m_nToOctave);

      this->Calc_SemitonesChange_fromPitches();
      this->Calc_PercentChange();

      m_bLoopDetect = true;
      {
         this->Update_Text_SemitonesChange();
         this->Update_Text_ToFrequency();
         this->Update_Text_PercentChange();
         this->Update_Slider_PercentChange();
      }
      m_bLoopDetect = false;
   }
}
