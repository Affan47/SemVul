text_splitter_retry(text_splitter *splitter)
{
	if (splitter->retry)
	{


		splitter->max_lines ++;
		splitter->retry = 0;
		splitter->unscaled_width = splitter->width * splitter->max_lines * splitter->fontsize
			/ splitter->height;
		splitter->scale = splitter->width / splitter->unscaled_width;
	}
	else
	{
		splitter->retry = 1;
	}
}
