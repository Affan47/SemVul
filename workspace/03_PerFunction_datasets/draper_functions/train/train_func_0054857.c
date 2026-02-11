rc_list_add(struct rc_list ** list, struct rc_list * new_value)
{
	struct rc_list * temp;

	if (*list == NULL) {
		*list = new_value;
		return;
	}

	for (temp = *list; temp->Next; temp = temp->Next);

	temp->Next = new_value;
	new_value->Prev = temp;
}
