wxt_put_text(unsigned int x, unsigned int y, const char * string)
{
	if (wxt_status != STATUS_OK)
		return;

	gp_command temp_command;


	if (wxt_enhanced_enabled && !ignore_enhanced_text) {


		temp_command.command = command_enhanced_init;
		temp_command.integer_value = strlen(string);
		wxt_command_push(temp_command);


		enhanced_fontscale = wxt_set_fontscale;
		strncpy(enhanced_escape_format, "%c", sizeof(enhanced_escape_format));


		while (*(string = enhanced_recursion((char*)string, TRUE, wxt_current_plot->fontname,
				wxt_current_plot->fontsize * wxt_set_fontscale,
				0.0, TRUE, TRUE, 0))) {
			wxt_enhanced_flush();


			enh_err_check(string);

			if (!*++string)
				break;

		}


		temp_command.command = command_enhanced_finish;
		temp_command.x1 = x;
		temp_command.y1 = term->ymax - y;
		wxt_command_push(temp_command);
		return;
	}

	temp_command.command = command_put_text;

	temp_command.x1 = x;
	temp_command.y1 = term->ymax - y;

	temp_command.string = new char[strlen(string)+1];
	strcpy(temp_command.string, string);

	wxt_command_push(temp_command);
}
