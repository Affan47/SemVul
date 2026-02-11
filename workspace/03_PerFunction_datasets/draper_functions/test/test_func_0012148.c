mk_signature_array(value ty, struct stub_dbus_sig *sig)
{
	int array_c_type;

	signature_append(sig, DBUS_TYPE_ARRAY);
	array_c_type = __type_array_table[Tag_val(ty)];
	if (IS_BASIC(array_c_type) || array_c_type == DBUS_TYPE_VARIANT) {
		signature_append(sig, array_c_type);
	} else if (array_c_type == DBUS_TYPE_DICT_ENTRY) {
		value sigtuple = Field(ty, 0);
		mk_signature_dict(Field(sigtuple, 0), Field(sigtuple, 1), sig);
	} else if (array_c_type == DBUS_TYPE_STRUCT) {
		mk_signature_structs(ty, sig);
	} else if (array_c_type == DBUS_TYPE_ARRAY) {
		mk_signature_arrays(Field(ty, 0), sig);
	} else {
		raise_dbus_type_not_supported("signature of array of unknown types");
	}
	DEBUG_SIG("array: %s (offset=%d)\n", s, offset);
}
