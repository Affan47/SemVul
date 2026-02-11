gamma_correct(int v, float gamma)
{
   v = (int)(powf((float)v / 255.0f, gamma) * 255);
   if(v > 255) v = 255;
   return(v);
}
