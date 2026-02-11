get_caller_no_reflection_related (MonoMethod *m, gint32 no, gint32 ilo, gboolean managed, gpointer data)
{
	MonoMethod **dest = (MonoMethod **)data;
	const char *ns;


	if (!managed)
		return FALSE;

	if (m->wrapper_type != MONO_WRAPPER_NONE)
		return FALSE;


	ns = m->klass->name_space;
	if (!ns || (*ns != 'S')) {
		*dest = m;
		return TRUE;
	}


	if (!mono_security_core_clr_is_platform_image (m->klass->image)) {
		*dest = m;
		return TRUE;
	}


	if (strcmp (ns, "System.Reflection") == 0)
		return FALSE;


	if (strcmp (ns, "System.Reflection.Emit") == 0)
		return FALSE;


	if (strcmp (ns, "System") == 0) {
		const char *kname = m->klass->name;
		if ((*kname == 'A') && (strcmp (kname, "Activator") == 0))
			return FALSE;


		if (((*kname == 'T') && (strcmp (kname, "Type") == 0)) ||
			((*kname == 'M') && (strcmp (kname, "MonoType")) == 0)) {


			if (strcmp (m->name, "InvokeMember") == 0)
				return FALSE;
		}


		if (((*kname == 'D') && (strcmp (kname, "Delegate") == 0)) ||
			((*kname == 'M') && (strcmp (kname, "MulticastDelegate")) == 0)) {


			if (strcmp (m->name, "DynamicInvoke") != 0)
				return FALSE;
		}
	}

	if (m == *dest) {
		*dest = NULL;
		return FALSE;
	}

	*dest = m;
	return TRUE;
}
