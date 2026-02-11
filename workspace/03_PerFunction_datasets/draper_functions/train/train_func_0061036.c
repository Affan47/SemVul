detect_minutiae_V2(MINUTIAE *minutiae,
            unsigned char *bdata, const int iw, const int ih,
            int *direction_map, int *low_flow_map, int *high_curve_map,
            const int mw, const int mh,
            const LFSPARMS *lfsparms)
{
   int ret;
   int *pdirection_map, *plow_flow_map, *phigh_curve_map;


   if((ret = pixelize_map(&pdirection_map, iw, ih, direction_map, mw, mh,
                         lfsparms->blocksize))){
      return(ret);
   }

   if((ret = pixelize_map(&plow_flow_map, iw, ih, low_flow_map, mw, mh,
                         lfsparms->blocksize))){
      free(pdirection_map);
      return(ret);
   }

   if((ret = pixelize_map(&phigh_curve_map, iw, ih, high_curve_map, mw, mh,
                         lfsparms->blocksize))){
      free(pdirection_map);
      free(plow_flow_map);
      return(ret);
   }

   if((ret = scan4minutiae_horizontally_V2(minutiae, bdata, iw, ih,
                 pdirection_map, plow_flow_map, phigh_curve_map, lfsparms))){
      free(pdirection_map);
      free(plow_flow_map);
      free(phigh_curve_map);
      return(ret);
   }

   if((ret = scan4minutiae_vertically_V2(minutiae, bdata, iw, ih,
                 pdirection_map, plow_flow_map, phigh_curve_map, lfsparms))){
      free(pdirection_map);
      free(plow_flow_map);
      free(phigh_curve_map);
      return(ret);
   }


   free(pdirection_map);
   free(plow_flow_map);
   free(phigh_curve_map);


   return(0);
}
