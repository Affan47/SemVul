read_header(dds_header_t *hdr, FILE *fp)
{
   unsigned char buf[DDS_HEADERSIZE];

   memset(hdr, 0, sizeof(dds_header_t));

   if(fread(buf, 1, DDS_HEADERSIZE, fp) != DDS_HEADERSIZE)
      return(0);

   hdr->magic[0] = buf[0];
   hdr->magic[1] = buf[1];
   hdr->magic[2] = buf[2];
   hdr->magic[3] = buf[3];

   hdr->size = GETL32(buf + 4);
   hdr->flags = GETL32(buf + 8);
   hdr->height = GETL32(buf + 12);
   hdr->width = GETL32(buf + 16);
   hdr->pitch_or_linsize = GETL32(buf + 20);
   hdr->depth = GETL32(buf + 24);
   hdr->num_mipmaps = GETL32(buf + 28);

   hdr->pixelfmt.size = GETL32(buf + 76);
   hdr->pixelfmt.flags = GETL32(buf + 80);
   hdr->pixelfmt.fourcc[0] = buf[84];
   hdr->pixelfmt.fourcc[1] = buf[85];
   hdr->pixelfmt.fourcc[2] = buf[86];
   hdr->pixelfmt.fourcc[3] = buf[87];
   hdr->pixelfmt.bpp = GETL32(buf + 88);
   hdr->pixelfmt.rmask = GETL32(buf + 92);
   hdr->pixelfmt.gmask = GETL32(buf + 96);
   hdr->pixelfmt.bmask = GETL32(buf + 100);
   hdr->pixelfmt.amask = GETL32(buf + 104);

   hdr->caps.caps1 = GETL32(buf + 108);
   hdr->caps.caps2 = GETL32(buf + 112);


   if(GETL32(buf + 32) == FOURCC('G','I','M','P') &&
      GETL32(buf + 36) == FOURCC('-','D','D','S'))
   {
      hdr->reserved.gimp_dds_special.magic1 = GETL32(buf + 32);
      hdr->reserved.gimp_dds_special.magic2 = GETL32(buf + 36);
      hdr->reserved.gimp_dds_special.version = GETL32(buf + 40);
      hdr->reserved.gimp_dds_special.extra_fourcc = GETL32(buf + 44);
   }

   return(1);
}
