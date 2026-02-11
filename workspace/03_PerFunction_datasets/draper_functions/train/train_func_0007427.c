UpdateModifiers( wxMouseEvent& event )
{
	int current_modifier_mask = 0;


	current_modifier_mask |= (event.AltDown() ? (1<<2) : 0);
	current_modifier_mask |= (event.ControlDown() ? (1<<1) : 0);
	current_modifier_mask |= (event.ShiftDown() ? (1) : 0);


	if (modifier_mask != current_modifier_mask) {
		modifier_mask = current_modifier_mask;
		wxt_exec_event(GE_modifier, 0, 0, modifier_mask, 0, this->GetId());
	}
}
