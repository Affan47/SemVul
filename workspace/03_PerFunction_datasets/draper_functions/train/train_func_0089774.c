ElementButton (const Element& el_, Gtk::Tooltips& tips)
:	el (el_), group (el.get_property (P_GROUP)),
	period (el.get_property (P_PERIOD))
{
	set_label (el.symbol);

	tips.set_tip (*this, compose::ucompose (_("%1 (%2)"),
		el.get_property (P_NAME).get_string (), el.number));
}
