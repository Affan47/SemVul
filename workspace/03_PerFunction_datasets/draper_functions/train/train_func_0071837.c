open_files()
{
    create_file_names();

    if (input_file == 0)
    {
	input_file = fopen(input_file_name, "r");
	if (input_file == 0)
	    open_error(input_file_name);
    }

    action_file = fopen(action_file_name, "w");
    if (action_file == 0)
	open_error(action_file_name);

    prolog_file = fopen(prolog_file_name, "w");
    if (prolog_file == 0)
	open_error(prolog_file_name);

    local_file = fopen(local_file_name, "w");
    if (local_file == 0)
	open_error(local_file_name);

    if (vflag)
    {
	verbose_file = fopen(verbose_file_name, "w");
	if (verbose_file == 0)
	    open_error(verbose_file_name);
    }
}
