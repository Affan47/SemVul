mono_string_is_interned_lookup (MonoString *str, int insert)
{
	MONO_REQ_GC_UNSAFE_MODE;

	MonoGHashTable *ldstr_table;
	MonoString *s, *res;
	MonoDomain *domain;

	domain = ((MonoObject *)str)->vtable->domain;
	ldstr_table = domain->ldstr_table;
	ldstr_lock ();
	res = (MonoString *)mono_g_hash_table_lookup (ldstr_table, str);
	if (res) {
		ldstr_unlock ();
		return res;
	}
	if (insert) {

		ldstr_unlock ();
		s = mono_string_get_pinned (str);
		if (s) {
			ldstr_lock ();
			res = (MonoString *)mono_g_hash_table_lookup (ldstr_table, str);
			if (res) {
				ldstr_unlock ();
				return res;
			}
			mono_g_hash_table_insert (ldstr_table, s, s);
			ldstr_unlock ();
		}
		return s;
	} else {
		LDStrInfo ldstr_info;
		ldstr_info.orig_domain = domain;
		ldstr_info.ins = str;
		ldstr_info.res = NULL;

		mono_domain_foreach (str_lookup, &ldstr_info);
		if (ldstr_info.res) {


			mono_g_hash_table_insert (ldstr_table, str, str);
			ldstr_unlock ();
			return str;
		}
	}
	ldstr_unlock ();
	return NULL;
}
