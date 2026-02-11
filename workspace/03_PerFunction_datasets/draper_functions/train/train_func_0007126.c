midgard_validable_is_valid (MidgardValidable *self)
{
	if (MIDGARD_VALIDABLE_GET_INTERFACE (self)->is_valid == NULL) {
		return FALSE;
	}

	return MIDGARD_VALIDABLE_GET_INTERFACE (self)->is_valid (self);
}
