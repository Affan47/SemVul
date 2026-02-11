mono_method_can_access_field_full (MonoMethod *method, MonoClassField *field, MonoClass *context_klass)
{
	MonoClass *access_class = method->klass;
	MonoClass *member_class = field->parent;

	int can = can_access_member (access_class, member_class, context_klass, field->type->attrs & FIELD_ATTRIBUTE_FIELD_ACCESS_MASK);
	if (!can) {
		MonoClass *nested = access_class->nested_in;
		while (nested) {
			can = can_access_member (nested, member_class, context_klass, field->type->attrs & FIELD_ATTRIBUTE_FIELD_ACCESS_MASK);
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
	return TRUE;
}
