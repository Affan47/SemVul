mono_method_can_access_method_full (MonoMethod *method, MonoMethod *called, MonoClass *context_klass)
{
	MonoClass *access_class = method->klass;
	MonoClass *member_class = called->klass;
	int can = can_access_member (access_class, member_class, context_klass, called->flags & METHOD_ATTRIBUTE_MEMBER_ACCESS_MASK);
	if (!can) {
		MonoClass *nested = access_class->nested_in;
		while (nested) {
			can = can_access_member (nested, member_class, context_klass, called->flags & METHOD_ATTRIBUTE_MEMBER_ACCESS_MASK);
			if (can)
				break;
			nested = nested->nested_in;
		}
	}

	if (!can)
		return FALSE;

	can = can_access_type (access_class, member_class);
	if (!can) {
		MonoClass *nested = access_class->nested_in;
		while (nested) {
			can = can_access_type (nested, member_class);
			if (can)
				break;
			nested = nested->nested_in;
		}
	}

	if (!can)
		return FALSE;

	if (called->is_inflated) {
		MonoMethodInflated * infl = (MonoMethodInflated*)called;
		if (infl->context.method_inst && !can_access_instantiation (access_class, infl->context.method_inst))
			return FALSE;
	}

	return TRUE;
}
