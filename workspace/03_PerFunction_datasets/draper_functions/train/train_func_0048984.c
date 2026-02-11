zChar2FragFrame(frame_t frag_frame, zSfeature *f)
{


	f->lfrag = frag_frame & 3;
	f->rfrag = (frag_frame & (3 << 2)) >> 2;
	f->frame = (frag_frame & (3 << 4)) >> 4;


	if (f->lfrag == 3) f->lfrag = -1;
	if (f->rfrag == 3) f->rfrag = -1;
	if (f->frame == 3) f->frame = -1;
}
