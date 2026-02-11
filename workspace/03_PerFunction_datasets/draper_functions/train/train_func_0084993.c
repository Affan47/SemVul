Update_Slider_PercentChange()
{
   if (m_pSlider_PercentChange) {
      double unwarped = m_PercentChange;
      if (unwarped > 0.0)

         unwarped = pow(m_PercentChange, (1.0 / PERCENTCHANGE_SLIDER_WARP));


      m_pSlider_PercentChange->SetValue((int)(unwarped + 0.5));
   }
}
