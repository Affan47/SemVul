tp_process_repeating_action(Gpm_Event *state, int feature, int last_feature, int *last_action,
			    touchpad_action_type *action_list,int feature_mask)
{
  if (feature) {
    if (!(last_feature && *last_action == GPM_B_NOT_SET)) {
      *last_action = tp_process_action(action_list, feature_mask);
      if (*last_action != GPM_B_NOT_SET)
	state->buttons |= *last_action;
    }
  } else {
      *last_action = GPM_B_NOT_SET;
  }
}
