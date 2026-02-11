DibReadBitmapInfo(CxFile* fh, BITMAPINFOHEADER *pdib)
{
	if ((fh==NULL)||(pdib==NULL)) return false;

    if (fh->Read(pdib,sizeof(BITMAPINFOHEADER),1)==0) return false;

	bihtoh(pdib);

    switch (pdib->biSize)
    {
        case sizeof(BITMAPINFOHEADER):
            break;

		case 64:
            fh->Seek((long)(64 - sizeof(BITMAPINFOHEADER)),SEEK_CUR);
			break;

        case sizeof(BITMAPCOREHEADER):
		{
            BITMAPCOREHEADER bc = *(BITMAPCOREHEADER*)pdib;
            pdib->biSize               = bc.bcSize;
            pdib->biWidth              = (DWORD)bc.bcWidth;
            pdib->biHeight             = (DWORD)bc.bcHeight;
            pdib->biPlanes             =  bc.bcPlanes;
            pdib->biBitCount           =  bc.bcBitCount;
            pdib->biCompression        = BI_RGB;
            pdib->biSizeImage          = 0;
            pdib->biXPelsPerMeter      = 0;
            pdib->biYPelsPerMeter      = 0;
            pdib->biClrUsed            = 0;
            pdib->biClrImportant       = 0;

			fh->Seek((long)(sizeof(BITMAPCOREHEADER)-sizeof(BITMAPINFOHEADER)), SEEK_CUR);
		}
            break;
        default:

			 if (pdib->biSize>(sizeof(BITMAPINFOHEADER))&&
				(pdib->biSizeImage>=(unsigned long)(pdib->biHeight*((((pdib->biBitCount*pdib->biWidth)+31)/32)*4)))&&
				(pdib->biPlanes==1)&&(pdib->biClrUsed==0))
			 {
	             if (pdib->biCompression==BI_RGB)
					 fh->Seek((long)(pdib->biSize - sizeof(BITMAPINFOHEADER)),SEEK_CUR);
				 break;
			 }
			return false;
    }

    FixBitmapInfo(pdib);

    return true;
}
