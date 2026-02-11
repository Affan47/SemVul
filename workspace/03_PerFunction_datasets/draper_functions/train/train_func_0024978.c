ves_icall_System_Security_Policy_Evidence_IsAuthenticodePresent (MonoReflectionAssembly *refass)
{
	if (refass && refass->assembly && refass->assembly->image) {
		return mono_image_has_authenticode_entry (refass->assembly->image);
	}
	return FALSE;
}
