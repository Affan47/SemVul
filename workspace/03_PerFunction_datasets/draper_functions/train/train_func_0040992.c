BarController (Gtk::Adjustment& adj,
			      PBD::Controllable& mc,
			      sigc::slot<void,char*,unsigned int> lc)

	: adjustment (adj),
	  binding_proxy (&mc),
	  label_callback (lc),
	  spinner (adjustment)

{
	_style = LeftToRight;
	grabbed = false;
	switching = false;
	switch_on_release = false;
	with_text = true;
	use_parent = false;
	logarithmic = false;

	layout = darea.create_pango_layout("");

	set_shadow_type (SHADOW_NONE);

	initial_value = adjustment.get_value ();

	adjustment.signal_value_changed().connect (mem_fun (*this, &Gtk::Widget::queue_draw));
	adjustment.signal_changed().connect (mem_fun (*this, &Gtk::Widget::queue_draw));

	darea.add_events (Gdk::BUTTON_RELEASE_MASK|
			  Gdk::BUTTON_PRESS_MASK|
			  Gdk::POINTER_MOTION_MASK|
			  Gdk::ENTER_NOTIFY_MASK|
			  Gdk::LEAVE_NOTIFY_MASK|
			  Gdk::SCROLL_MASK);

	darea.signal_expose_event().connect (mem_fun (*this, &BarController::expose));
	darea.signal_motion_notify_event().connect (mem_fun (*this, &BarController::motion));
	darea.signal_button_press_event().connect (mem_fun (*this, &BarController::button_press), false);
	darea.signal_button_release_event().connect (mem_fun (*this, &BarController::button_release), false);
	darea.signal_scroll_event().connect (mem_fun (*this, &BarController::scroll));

	spinner.signal_activate().connect (mem_fun (*this, &BarController::entry_activated));
	spinner.signal_focus_out_event().connect (mem_fun (*this, &BarController::entry_focus_out));
	spinner.signal_output().connect (mem_fun (*this, &BarController::entry_output));
	spinner.signal_input().connect (mem_fun (*this, &BarController::entry_input));
	spinner.set_digits (3);
	spinner.set_numeric (true);

	add (darea);
	show_all ();
}
