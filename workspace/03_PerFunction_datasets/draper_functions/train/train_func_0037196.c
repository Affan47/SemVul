filepanel_read(void)
{
	filepos_save();
	if (ppanel_file->pd->filtering) {

		ppanel_file->pd->cnt = ppanel_file->filt_cnt;
		ppanel_file->selected += ppanel_file->filt_sel;
	}
	directory_read();
	if (ppanel_file->pd->filtering) {

		ppanel_file->filt_cnt = ppanel_file->pd->cnt;
		ppanel_file->pd->filter->changed = 1;
	}
	else
		sort_files();
	filepos_set();
	ppanel_file->expired = 0;
}
