acpi_ps_get_next_namestring(struct acpi_parse_state *parser_state)
{
	u8 *start = parser_state->aml;
	u8 *end = parser_state->aml;

	ACPI_FUNCTION_TRACE(ps_get_next_namestring);


	while (ACPI_IS_ROOT_PREFIX(*end) || ACPI_IS_PARENT_PREFIX(*end)) {
		end++;
	}


	switch (*end) {
	case 0:


		if (end == start) {
			start = NULL;
		}
		end++;
		break;

	case AML_DUAL_NAME_PREFIX:


		end += 1 + (2 * ACPI_NAME_SIZE);
		break;

	case AML_MULTI_NAME_PREFIX_OP:


		end += 2 + (*(end + 1) * ACPI_NAME_SIZE);
		break;

	default:


		end += ACPI_NAME_SIZE;
		break;
	}

	parser_state->aml = end;
	return_PTR((char *)start);
}
