print_ext(struct file_ext *ext)
{
	if (ext->end_blk == 0)
		printf("%8d    %8d    %8d    %8d\n", ext->f_pos, 0, 0, ext->blk_count);
	else
		printf("%8d    %8d    %8d    %8d\n", ext->f_pos, ext->start_blk,
					ext->end_blk, ext->blk_count);
}
