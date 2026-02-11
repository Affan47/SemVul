_k_disable_delete_for_now(state_t *s, reg_t obj)
{
  	reg_t text_pos = GET_SEL32(obj, text);
	char *text = IS_NULL_REG(text_pos)? NULL : (char *) sm_dereference(&s->seg_manager, text_pos, NULL);
	int type = GET_SEL32V(obj, type);
	int state = GET_SEL32V(obj, state);

	if (type == K_CONTROL_BUTTON && text &&
	    !strcmp(s->game_name, "sq4") &&
	    s->version < SCI_VERSION(1,001,000) &&
	    !strcmp(text, " Delete "))
		PUT_SEL32V(obj, state, (state | CONTROL_STATE_GRAY) & ~CONTROL_STATE_ENABLED);
}
