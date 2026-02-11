cmdi_cmd()
{
void *tmp;


    while (orn_list) {

	cmdi_handle_ntf (orn_list->orn);


	tmp = orn_list;
	orn_list = orn_list->next;
	free (tmp);
    }


    while (cmd_input) {


	cmdi_parse (cmd_input);


	tmp = cmd_input;
	cmd_input = cmd_input->next;
	free (tmp);
    }

    return;
}
