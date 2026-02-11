DCM_RLE_ReadByte(Image *image, DicomStream *dcm)
{
  if (dcm->rle_rep_ct == 0)
    {
      int
        rep_ct,
        rep_char;


      if (dcm->frag_bytes <= 2)
        dcm->frag_bytes = 0;
      else
        dcm->frag_bytes -= 2;

      rep_ct=ReadBlobByte(image);
      rep_char=ReadBlobByte(image);
      if (rep_ct == 128)
        {

          return 0;
        }
      else
      if (rep_ct < 128)
        {

          dcm->rle_rep_ct=rep_ct;
          dcm->rle_rep_char=-1;
          return (magick_uint8_t)rep_char;
        }
      else
        {

          dcm->rle_rep_ct=256-rep_ct;
          dcm->rle_rep_char=rep_char;
          return (magick_uint8_t)rep_char;
        }
    }

  dcm->rle_rep_ct--;
  if (dcm->rle_rep_char >= 0)
    return dcm->rle_rep_char;

  if (dcm->frag_bytes > 0)
    dcm->frag_bytes--;
  return ReadBlobByte(image);
}
