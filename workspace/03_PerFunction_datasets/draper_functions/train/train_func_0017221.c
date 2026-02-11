OnDepthText(wxCommandEvent & WXUNUSED(event))
{
   wxTextCtrl *c = GetDepthText();
   if (c) {
      long depth;

      c->GetValue().ToLong(&depth);
      depth = TrapLong(depth, DEPTH_MIN, DEPTH_MAX);

      wxSlider *slider = GetDepthSlider();
      if (slider)
         slider->SetValue(depth);
   }
}
