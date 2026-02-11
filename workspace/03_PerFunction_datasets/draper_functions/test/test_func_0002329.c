buffer_add_assemblyid (Buffer *buf, MonoDomain *domain, MonoAssembly *assembly)
{
	int id;

	id = buffer_add_ptr_id (buf, domain, ID_ASSEMBLY, assembly);
	if (G_UNLIKELY (log_level >= 2) && assembly)
		DEBUG_PRINTF (2, "[dbg]   send assembly [%s][%s][%d]\n", assembly->aname.name, domain->friendly_name, id);
}
