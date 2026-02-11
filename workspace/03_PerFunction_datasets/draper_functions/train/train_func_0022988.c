intel_cb(Fl_Widget*, void*) {
  if (!intel_window) {
    intel_window = new Fl_Window(200,25,"Checkers Intelligence");
    Fl_Slider* s = new Fl_Slider(60,0,140,25);
    s->type(FL_HOR_NICE_SLIDER);
    s->minimum(1); s->maximum(500); s->value(50);
    s->callback(intel_slider_cb);
    intel_output = new Fl_Value_Output(0,0,60,25);
    intel_output->value(maxevaluate);
    intel_window->resizable(s);
  }
  intel_window->hotspot(intel_window);
  intel_window->set_non_modal();
  intel_window->show();
}
