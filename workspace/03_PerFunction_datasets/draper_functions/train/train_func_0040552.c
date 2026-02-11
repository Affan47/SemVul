load_fileinfo(cchar *file)
{
   void exif_tagdate(cchar *exifdate, char *tagdate);

   int         ii, jj, cc;
   char        *pp;
   cchar       *exifkeys[5] = { exif_date_key, iptc_tags_key, iptc_rating_key,
                                exif_comment_key, iptc_caption_key };
   char        **ppv, *imagedate, *imagetags, *imagestars, *imagecomms, *imagecapt;

   *tags_filetags = *tags_date = *tags_comments = *tags_caption = 0;
   tags_stars = '0';

   ppv = info_get(file,exifkeys,5);
   imagedate = ppv[0];
   imagetags = ppv[1];
   imagestars = ppv[2];
   imagecomms = ppv[3];
   imagecapt = ppv[4];

   if (imagedate) {
      exif_tagdate(imagedate,tags_date);
      strcpy(tags_prdate,tags_date);
      zfree(imagedate);
   }

   if (imagetags)
   {
      for (ii = 1; ; ii++)
      {
         pp = (char *) strField(imagetags,tagdelims,ii);
         if (! pp) break;
         if (*pp == ' ') continue;
         cc = strlen(pp);
         if (cc >= tagcc) continue;
         for (jj = 0; jj < cc; jj++)
            if (pp[jj] > 0 && pp[jj] < ' ') break;
         if (jj < cc) continue;
         add_tag(pp,tags_filetags,tagFcc);
      }

      zfree(imagetags);
   }

   if (imagestars) {
      tags_stars = *imagestars;
      if (tags_stars < '0' || tags_stars > '5') tags_stars = '0';
      zfree(imagestars);
   }

   if (imagecomms) {
      strncpy0(tags_comments,imagecomms,tagFcc);
      zfree(imagecomms);
   }

   if (imagecapt) {
      strncpy0(tags_caption,imagecapt,tagFcc);
      zfree(imagecapt);
   }

   Ftagschanged = 0;
   return;
}
