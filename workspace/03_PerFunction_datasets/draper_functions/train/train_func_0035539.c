rle_flush(struct_RLE* rle)
{
	if (rle->rl_count == 1){
		rle_output_plain(rle->rl_pixel,rle);
		rle->rl_count = 0;
		return;
	}
	if (rle->just_cleared){
		rle_flush_fromclear(rle->rl_count,rle);
	} else if ((rle->rl_table_max < 2) || (rle->rl_table_pixel != rle->rl_pixel)) {
		rle_flush_clearorrep(rle->rl_count,rle);
	} else {
		rle_flush_withtable(rle->rl_count,rle);
	}
	rle->rl_count = 0;
}
