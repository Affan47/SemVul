acpi_install_method(u8 *buffer)
{
	struct acpi_table_header *table =
	    ACPI_CAST_PTR(struct acpi_table_header, buffer);
	u8 *aml_buffer;
	u8 *aml_start;
	char *path;
	struct acpi_namespace_node *node;
	union acpi_operand_object *method_obj;
	struct acpi_parse_state parser_state;
	u32 aml_length;
	u16 opcode;
	u8 method_flags;
	acpi_status status;


	if (!buffer) {
		return (AE_BAD_PARAMETER);
	}


	if (!ACPI_COMPARE_NAME(table->signature, ACPI_SIG_DSDT) &&
	    !ACPI_COMPARE_NAME(table->signature, ACPI_SIG_SSDT)) {
		return (AE_BAD_HEADER);
	}


	parser_state.aml = buffer + sizeof(struct acpi_table_header);
	opcode = acpi_ps_peek_opcode(&parser_state);
	if (opcode != AML_METHOD_OP) {
		return (AE_BAD_PARAMETER);
	}


	parser_state.aml += acpi_ps_get_opcode_size(opcode);
	parser_state.pkg_end = acpi_ps_get_next_package_end(&parser_state);
	path = acpi_ps_get_next_namestring(&parser_state);
	method_flags = *parser_state.aml++;
	aml_start = parser_state.aml;
	aml_length = ACPI_PTR_DIFF(parser_state.pkg_end, aml_start);


	aml_buffer = ACPI_ALLOCATE(aml_length);
	if (!aml_buffer) {
		return (AE_NO_MEMORY);
	}

	method_obj = acpi_ut_create_internal_object(ACPI_TYPE_METHOD);
	if (!method_obj) {
		ACPI_FREE(aml_buffer);
		return (AE_NO_MEMORY);
	}


	status = acpi_ut_acquire_mutex(ACPI_MTX_NAMESPACE);
	if (ACPI_FAILURE(status)) {
		goto error_exit;
	}


	status =
	    acpi_ns_lookup(NULL, path, ACPI_TYPE_METHOD, ACPI_IMODE_LOAD_PASS1,
			   ACPI_NS_DONT_OPEN_SCOPE | ACPI_NS_ERROR_IF_FOUND,
			   NULL, &node);

	(void)acpi_ut_release_mutex(ACPI_MTX_NAMESPACE);

	if (ACPI_FAILURE(status)) {
		if (status != AE_ALREADY_EXISTS) {
			goto error_exit;
		}


		if (node->type != ACPI_TYPE_METHOD) {
			status = AE_TYPE;
			goto error_exit;
		}
	}


	memcpy(aml_buffer, aml_start, aml_length);


	method_obj->method.aml_start = aml_buffer;
	method_obj->method.aml_length = aml_length;

	method_obj->method.param_count = (u8)
	    (method_flags & AML_METHOD_ARG_COUNT);

	if (method_flags & AML_METHOD_SERIALIZED) {
		method_obj->method.info_flags = ACPI_METHOD_SERIALIZED;

		method_obj->method.sync_level = (u8)
		    ((method_flags & AML_METHOD_SYNC_LEVEL) >> 4);
	}


	status = acpi_ns_attach_object(node, method_obj, ACPI_TYPE_METHOD);


	node->flags |= ANOBJ_ALLOCATED_BUFFER;


	acpi_ut_remove_reference(method_obj);
	return (status);

error_exit:

	ACPI_FREE(aml_buffer);
	ACPI_FREE(method_obj);
	return (status);
}
