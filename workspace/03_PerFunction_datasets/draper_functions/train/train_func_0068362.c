add_arg(struct data_list **last_data, char *argv)
{
	struct data_list *data;

	while(*last_data)
	        last_data = &((*last_data)->next);

	data = malloc(sizeof(struct data_list));
	if(data) {
		data->next = NULL;
		data->data = argv;
		*last_data = data;
		last_data = &data->next;
	} else {
		printf("Error: Unable to allocate memory\n");
		return(False);
	}
	return(True);
}
