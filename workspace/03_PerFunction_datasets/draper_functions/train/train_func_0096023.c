shield_set_strength(object *objp, float strength)
{
	int	i;

	for (i = 0; i < MAX_SHIELD_SECTIONS; i++)
		shield_set_quad(objp, i, strength / MAX_SHIELD_SECTIONS);
}
