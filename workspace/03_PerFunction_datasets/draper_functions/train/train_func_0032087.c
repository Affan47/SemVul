MetaSect2Free (grib_MetaData *meta)
{
   size_t i;

   for (i = 0; i < meta->pds2.sect2.wx.dataLen; i++) {
      free (meta->pds2.sect2.wx.data[i]);
      FreeUglyString (&(meta->pds2.sect2.wx.ugly[i]));
   }
   free (meta->pds2.sect2.wx.ugly);
   meta->pds2.sect2.wx.ugly = NULL;
   free (meta->pds2.sect2.wx.data);
   meta->pds2.sect2.wx.data = NULL;
   meta->pds2.sect2.wx.dataLen = 0;
   meta->pds2.sect2.wx.maxLen = 0;
   meta->pds2.sect2.ptrType = GS2_NONE;

   free (meta->pds2.sect2.wx.data);
   meta->pds2.sect2.unknown.data = NULL;
   meta->pds2.sect2.unknown.dataLen = 0;
}
