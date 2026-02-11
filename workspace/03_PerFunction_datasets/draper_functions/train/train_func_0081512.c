stc_expand(stcolor_device *sd,int i,gx_color_index col)
{

   gx_color_index cv;
   gx_color_index l = (1<<sd->stc.bits)-1;

   if(sd->stc.code[i] != NULL) {

      cv  = sd->stc.code[i][col & l];

   } else if(sd->stc.bits < gx_color_value_bits) {

      cv  = (col & l)<<(gx_color_value_bits-sd->stc.bits);
      cv += (col & l)/l * ((1<<(gx_color_value_bits-sd->stc.bits))-1);

   } else if(sd->stc.bits > gx_color_value_bits) {

      cv  = (col & l)>>(sd->stc.bits-gx_color_value_bits);

   } else {

      cv  = col & l;

   }

   return cv;
}
