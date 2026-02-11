stc_any_depth(stcolor_device *sd,byte *ext_data,int prt_pixels,byte *alg_line)
{

   int p,c,       niext,         nbits;
   gx_color_index ciext,ci,cimsk,cvmsk;
   byte          *ap = alg_line;

   nbits =  sd->stc.bits;
   cvmsk = ((gx_color_index) 1<<nbits) - 1;


   if(sd->color_info.depth == (sd->color_info.num_components<<3)) nbits = 8;

   cimsk = cvmsk;
   for(c = 1; c < sd->color_info.num_components; ++c)
       cimsk = (cimsk<<nbits) | cvmsk;

   ciext = 0;
   niext = 0;

   for(p = 0; p < prt_pixels; ++p) {

      ci = ciext;
      for(c =  sd->color_info.depth-niext; c >= 8; c -= 8)
         ci  = (ci<<8) | *ext_data++;

      if(c > 0) {

         niext  = 8 - c;
         ciext  = *ext_data++;
         ci     = (ci<<c) | (ciext>>niext);
         ciext &= (1L<<niext)-1;

      } else if(c < 0) {

         niext  = -c;
         ciext &= (1L<<niext)-1;
         ci     = ci>>niext;

      } else {

         niext = 0;
         ciext = 0;

      }

      ci &= cimsk;

#     define stc_storeapc(T) \
         ((T *)ap)[c] = ((T *)(sd->stc.vals[c]))[ci & cvmsk];

      for(c = sd->color_info.num_components; c--;) {
         STC_TYPESWITCH(sd->stc.dither,stc_storeapc)
         ci >>= nbits;
      }

#     undef  stc_storeapc

      ap += sd->color_info.num_components * sd->stc.alg_item;

   }

   return alg_line;
}
