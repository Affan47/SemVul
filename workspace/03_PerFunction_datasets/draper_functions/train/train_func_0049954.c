acpi_ds_exec_begin_control_op(struct acpi_walk_state *walk_state,
			      union acpi_parse_object *op)
{
	acpi_status status = AE_OK;
	union acpi_generic_state *control_state;

	ACPI_FUNCTION_NAME(ds_exec_begin_control_op);

	ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH, "Op=%p Opcode=%2.2X State=%p\n",
			  op, op->common.aml_opcode, walk_state));

	switch (op->common.aml_opcode) {
	case AML_WHILE_OP:


		if (walk_state->control_state) {
			if (walk_state->control_state->control.
			    aml_predicate_start ==
			    (walk_state->parser_state.aml - 1)) {


				walk_state->control_state->common.state =
				    ACPI_CONTROL_CONDITIONAL_EXECUTING;
				break;
			}
		}


	case AML_IF_OP:


		control_state = acpi_ut_create_control_state();
		if (!control_state) {
			status = AE_NO_MEMORY;
			break;
		}


		control_state->control.aml_predicate_start =
		    walk_state->parser_state.aml - 1;
		control_state->control.package_end =
		    walk_state->parser_state.pkg_end;
		control_state->control.opcode = op->common.aml_opcode;


		acpi_ut_push_generic_state(&walk_state->control_state,
					   control_state);
		break;

	case AML_ELSE_OP:


		if (walk_state->last_predicate) {
			status = AE_CTRL_TRUE;
		}

		break;

	case AML_RETURN_OP:

		break;

	default:

		break;
	}

	return (status);
}
