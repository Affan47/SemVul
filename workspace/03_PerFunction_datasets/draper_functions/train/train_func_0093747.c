hsv2rgb( HSV hsv)
{
   float h = float(hsv.h) / 360;
   float s = float(hsv.s) / 255;
   float v = float(hsv.v) / 255;


   if (hsv.s == 0) {
      return DI_Color(hsv.v, hsv.v, hsv.v);
   } else {
      float h2 = h * 6;
      if (h2 >= 6)
         h2 = 0;

      float var_i = floor(h2);

      float var_1 = v * (1 - s);
      float var_2 = v * (1 - s * (h2 - var_i));
      float var_3 = v * (1 - s * (1 - (h2 - var_i)));

      float var_r, var_g, var_b;
      if ( var_i == 0) {
         var_r = v;
         var_g = var_3;
         var_b = var_1;
      } else if (var_i == 1) {
         var_r = var_2;
         var_g = v;
         var_b = var_1;
      } else if (var_i == 2) {
         var_r = var_1;
         var_g = v;
         var_b = var_3;
      } else if (var_i == 3) {
         var_r = var_1;
         var_g = var_2;
         var_b = v;
      } else if (var_i == 4) {
         var_r = var_3;
         var_g = var_1;
         var_b = v;
      } else {
         var_r = v;
         var_g = var_1;
         var_b = var_2;
      }
      return DI_Color( int( ceil( var_r * 255 )),
                       int( ceil( var_g * 255 )),
                       int( ceil( var_b * 255 )));
   }

}
