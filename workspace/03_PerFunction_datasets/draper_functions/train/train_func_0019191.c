has_key_internal(int keycode, TRIES * tp)
{
    if (tp == 0)
	return (FALSE);
    else if (tp->value == keycode)
	return (TRUE);
    else
	return (has_key_internal(keycode, tp->child)
		|| has_key_internal(keycode, tp->sibling));
}
