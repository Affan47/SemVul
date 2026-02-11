create_domain_objects (MonoDomain *domain)
{
	MonoDomain *old_domain = mono_domain_get ();
	MonoString *arg;
	MonoVTable *string_vt;
	MonoClassField *string_empty_fld;

	if (domain != old_domain) {
		mono_thread_push_appdomain_ref (domain);
		mono_domain_set_internal_with_options (domain, FALSE);
	}


	string_vt = mono_class_vtable (domain, mono_defaults.string_class);
	string_empty_fld = mono_class_get_field_from_name (mono_defaults.string_class, "Empty");
	g_assert (string_empty_fld);
	mono_field_static_set_value (string_vt, string_empty_fld, mono_string_intern (mono_string_new (domain, "")));


	arg = mono_string_new (domain, "Out of memory");
	domain->out_of_memory_ex = mono_exception_from_name_two_strings (mono_defaults.corlib, "System", "OutOfMemoryException", arg, NULL);


	arg = mono_string_new (domain, "A null value was found where an object instance was required");
	domain->null_reference_ex = mono_exception_from_name_two_strings (mono_defaults.corlib, "System", "NullReferenceException", arg, NULL);
	arg = mono_string_new (domain, "The requested operation caused a stack overflow.");
	domain->stack_overflow_ex = mono_exception_from_name_two_strings (mono_defaults.corlib, "System", "StackOverflowException", arg, NULL);


	domain->ephemeron_tombstone = mono_object_new (domain, mono_defaults.object_class);

	if (domain != old_domain) {
		mono_thread_pop_appdomain_ref ();
		mono_domain_set_internal_with_options (old_domain, FALSE);
	}


	mono_class_init (mono_array_class_get (mono_defaults.int_class, 1));
}
