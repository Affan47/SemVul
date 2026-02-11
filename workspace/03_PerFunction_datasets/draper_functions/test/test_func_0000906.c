writeActions(
             AuServer       *aud,
             AuElementActionList *list
             )
{
    int             i;
    AuElementAction *action;
    auElementAction a;

    for (i = 0; i < list->num_actions; i++)
    {
	action = &list->actions[i];

#undef xfer
#define xfer(x) a.x = action->x
	xfer(flow);
	xfer(element_num);
	xfer(trigger_state);
	xfer(trigger_prev_state);
	xfer(trigger_reason);
	xfer(action);
	xfer(new_state);

	_AuData32(aud, &a, SIZEOF(auElementAction));
    }
}
