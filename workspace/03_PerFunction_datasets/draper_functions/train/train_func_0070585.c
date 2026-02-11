GrabWindowKey(Display *dpy, Window w, Binding *binding,
		   unsigned int contexts, unsigned int dead_modifiers,
		   Bool fGrab)
{

	dead_modifiers &= ~(binding->Modifier & dead_modifiers);
	dead_modifiers &= ALL_MODIFIERS;

	if((binding->Context & contexts) && BIND_IS_KEY_BINDING(binding->type))
	{
		if (fGrab)
		{
			XGrabKey(
				dpy, binding->Button_Key, binding->Modifier, w,
				True, GrabModeAsync, GrabModeAsync);
		}
		else
		{
			XUngrabKey(
				dpy, binding->Button_Key, binding->Modifier, w);
		}
		if(binding->Modifier != AnyModifier && dead_modifiers != 0)
		{
			register unsigned int mods;
			register unsigned int max = dead_modifiers;
			register unsigned int living_modifiers =
				~dead_modifiers;


			for (mods = 1; mods <= max; mods++)
			{


				if (mods & living_modifiers)
				{
					continue;
				}
				if (fGrab)
				{
					XGrabKey(
						dpy, binding->Button_Key,
						mods|binding->Modifier, w,
						True, GrabModeAsync,
						GrabModeAsync);
				}
				else
				{
					XUngrabKey(
						dpy, binding->Button_Key,
						mods|binding->Modifier, w);
				}
			}
		}
		if (!is_grabbing_everything)
		{
			XSync(dpy, 0);
		}
	}

	return;
}
