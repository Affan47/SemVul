midgard_object_set_connection(MidgardObject *self, MidgardConnection *mgd)
{
	g_assert(self != NULL);
	g_assert(mgd != NULL);

	if (MGD_OBJECT_CNC (self) != NULL)
		return;


	MGD_OBJECT_CNC (self) = g_object_ref (mgd);
}
