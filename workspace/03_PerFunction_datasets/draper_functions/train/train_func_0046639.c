OOGLgetcolor(QvMaterial *mt, QvMaterialBinding *mtb, int mtnum)
{

   float *em, *dif;
   float a;

   if (mt == NULL || mtnum < 0) { sprintf(colstr, "1 1 1 1"); return; }

   a = 1 - (mt->transparency).values[mtnum % (mt->transparency).num];
   em = &mt->emissiveColor.values[3 * (mtnum % mt->emissiveColor.num)];
   dif = &mt->diffuseColor.values[3 * (mtnum % mt->diffuseColor.num)];
   if (em[0] != 0.0 || em[1] != 0.0 || em[2] != 0.0) {

      float r, g, b, ln;
      r = em[0];
      g = em[1];
      b = em[2];
      ln = (3.0 - sqrt(r*r + g*g + b*b)) / 6.0;
      r += (1.0 - r)*ln; g += (1.0 - g)*ln; b += (1.0 - b)*ln;
      sprintf(colstr, "%.3f %.3f %.3f %.3f", r, g, b, a);
    }
    else
      sprintf(colstr, "%.3f %.3f %.3f %.3f", dif[0], dif[1], dif[2], a);

}
