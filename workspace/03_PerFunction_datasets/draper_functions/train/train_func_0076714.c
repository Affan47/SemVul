get_num_frames(CxFile *fp,struct_TabCol* TabColSrc,struct_dscgif* dscgif)
{
	struct_image image;

	long pos=fp->Tell();
	int nframes=0;

	struct_TabCol TempTabCol;
	memcpy(&TempTabCol,TabColSrc,sizeof(struct_TabCol));

	char ch;
	bool bPreviousWasNull = true;

	for (BOOL bContinue = TRUE; bContinue; )
	{
		if (fp->Read(&ch, sizeof(ch), 1) != 1) {break;}

		if (bPreviousWasNull || ch==0)
		{
			switch (ch)
			{
			case '!':
				{
				DecodeExtension(fp);
				break;
				}
			case ',':
				{

				assert(sizeof(image) == 9);

				fp->Read(&image,sizeof(image),1);


				image.l = xima_ntohs(image.l);
				image.t = xima_ntohs(image.t);
				image.w = xima_ntohs(image.w);
				image.h = xima_ntohs(image.h);


				if (dscgif->scrwidth==0 && dscgif->scrheight==0){
					dscgif->scrwidth = image.w;
					dscgif->scrheight = image.h;
				}

				if (((image.l + image.w) > dscgif->scrwidth)||((image.t + image.h) > dscgif->scrheight))
					break;

				nframes++;


				if (image.pf & 0x80) {
					TempTabCol.sogct = (short)(1 << ((image.pf & 0x07) +1));
					assert(3 == sizeof(struct rgb_color));
					fp->Read(TempTabCol.paleta,sizeof(struct rgb_color)*TempTabCol.sogct,1);

				}

				int badcode=0;
				ibf = GIFBUFTAM+1;

				interlaced = image.pf & 0x40;
				iheight = image.h;
				istep = 8;
				iypos = 0;
				ipass = 0;

				long pos_start = fp->Tell();


				decoder(fp, 0, image.w, badcode);

				if (badcode){
					seek_next_image(fp,pos_start);
				} else {
					fp->Seek(-(ibfmax - ibf - 1), SEEK_CUR);
				}

				break;
				}
			case ';':
				bContinue=false;
				break;
			default:
				bPreviousWasNull = (ch==0);
				break;
			}
		}
	}

	fp->Seek(pos,SEEK_SET);
	return nframes;
}
