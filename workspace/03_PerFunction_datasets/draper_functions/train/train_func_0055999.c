button_kill_text(unsigned char keypress)
{
	int i, j, length;


	for (i = 0; i < button_num; i++)
		if (button_mse[i].key == keypress) break;


	if (i == button_num)
	{
		return 0;
	}


	length = button_mse[i].right - button_mse[i].left + 1;
	button_length -= length;


	for (j = i; j < button_num - 1; j++)
	{
		button_mse[j] = button_mse[j + 1];


		button_mse[j].left -= length;
		button_mse[j].right -= length;
	}


	button_mse[button_num].label[0] = '\0';
	button_mse[button_num].left = 0;
	button_mse[button_num].right = 0;
	button_mse[button_num--].key = 0;


	p_ptr->redraw |= (PR_BUTTONS);
	redraw_stuff();


	return (length);
}
