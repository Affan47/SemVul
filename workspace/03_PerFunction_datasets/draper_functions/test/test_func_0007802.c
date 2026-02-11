acpiphp_disable_and_eject_slot(struct acpiphp_slot *slot)
{
	struct acpiphp_func *func;

	if (slot->flags & SLOT_IS_GOING_AWAY)
		return -ENODEV;


	disable_slot(slot);

	list_for_each_entry(func, &slot->funcs, sibling)
		if (func->flags & FUNC_HAS_EJ0) {
			acpi_handle handle = func_to_handle(func);

			if (ACPI_FAILURE(acpi_evaluate_ej0(handle)))
				acpi_handle_err(handle, "_EJ0 failed\n");

			break;
		}

	return 0;
}
