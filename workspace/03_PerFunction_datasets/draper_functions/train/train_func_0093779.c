write_blocks(filesystem *fs, uint32 nod, FILE* f)
{
	blockwalker bw;
	uint32 bk;
	int32 fsize = get_nod(fs, nod)->i_size;
	init_bw(&bw);
	while((bk = walk_bw(fs, nod, &bw, 0, 0)) != WALK_END)
	{
		if(fsize <= 0)
			error_msg_and_die("wrong size while saving inode %d", nod);
		if(fwrite(get_blk(fs, bk), (fsize > BLOCKSIZE) ? BLOCKSIZE : fsize, 1, f) != 1)
			error_msg_and_die("error while saving inode %d", nod);
		fsize -= BLOCKSIZE;
	}
}
