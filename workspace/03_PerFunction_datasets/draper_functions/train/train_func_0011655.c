bt_ctf_event_get_payload(struct bt_ctf_event *event,
		const char *name)
{
	struct bt_ctf_field *field = NULL;

	if (!event || !name) {
		goto end;
	}

	field = bt_ctf_field_structure_get_field(event->fields_payload, name);
end:
	return field;
}
