calc_plaintext( PKT_plaintext *pt )
{


  if(pt->namelen>255)
    pt->namelen=255;

  return pt->len? (1 + 1 + pt->namelen + 4 + pt->len) : 0;
}
