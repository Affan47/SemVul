ves_icall_System_Runtime_InteropServices_Marshal_GetObjectForCCW (void* pUnk)
{
#ifndef DISABLE_COM
	MonoObject* object = NULL;

	if (!pUnk)
		return NULL;


	object = cominterop_get_ccw_object ((MonoCCWInterface*)pUnk, TRUE);

	return object;
#else
	g_assert_not_reached ();
#endif
}
