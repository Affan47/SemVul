vee_data_equal (gconstpointer v1,
                gconstpointer v2)
{
	const VeeData *vee_data1 = v1, *vee_data2 = v2;

	if (!v1 || !v2)
		return v1 == v2;


	return v1 == v2 ||
		(vee_data1->folder == vee_data2->folder &&
		 vee_data1->orig_message_uid == vee_data2->orig_message_uid);
}
