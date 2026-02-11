do_cmd_spoilers(void)
{
	char ch;


	screen_save();


	while (1)
	{

		Term_clear();


		prt("Create a spoiler file.", 2, 0);


		prt("(1) Brief Object Info (obj-desc.spo)", 5, 5);
		prt("(2) Brief Artifact Info (artifact.spo)", 6, 5);
		prt("(3) Brief Monster Info (mon-desc.spo)", 7, 5);
		prt("(4) Full Monster Info (mon-info.spo)", 8, 5);


		prt("Command: ", 12, 0);


		ch = inkey();


		if (ch == ESCAPE)
		{
			break;
		}


		else if (ch == '1')
		{
			spoil_obj_desc("obj-desc.spo");
		}


		else if (ch == '2')
		{
			spoil_artifact("artifact.spo");
		}


		else if (ch == '3')
		{
			spoil_mon_desc("mon-desc.spo");
		}


		else if (ch == '4')
		{
			spoil_mon_info("mon-info.spo");
		}


		else
		{
			bell("Illegal command for spoilers!");
		}


		message_flush();
	}


	screen_load();
}
