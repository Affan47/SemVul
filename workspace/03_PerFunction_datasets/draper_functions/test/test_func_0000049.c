plD_tidy_png(PLStream *pls)
{

#ifdef HAVE_FREETYPE
   if (pls->dev_text)
     {
	FT_Data *FT=(FT_Data *)pls->FT;
	plscmap0n(FT->ncol0_org);
	plD_FreeType_Destroy(pls);
     }
#endif

   fclose(pls->OutFile);
   free_mem(pls->dev);
}
