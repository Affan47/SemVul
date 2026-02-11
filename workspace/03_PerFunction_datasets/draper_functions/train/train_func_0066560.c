premul_image(void)
{
   DATA32 *p, *end;

   end =  (DATA32 *)image->data + (image->width * image->height);
   for (p = (DATA32 *)image->data; p < end; p++)
     {
        unsigned int r, g, b, a;

        a = A_VAL(p);
        r = (R_VAL(p) * a) / 255;
        R_VAL(p) = r;
        g = (G_VAL(p) * a) / 255;
        G_VAL(p) = g;
        b = (B_VAL(p) * a) / 255;
        B_VAL(p) = b;
     }
}
