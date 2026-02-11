cpercep_space_to_rgb (double  inr,
                      double  ing,
                      double  inb,
                      double *outr,
                      double *outg,
                      double *outb)
{
  lab_to_xyz (&inr, &ing, &inb);

#ifdef SANITY
  if (inr < -0.0F || ing < -0.0F || inb < -0.0F)
    {
      g_printerr (" [BAD1 XYZ: %f,%f,%f]\007 ",
                  inr, ing, inb);
    }
#endif

  xyz_to_rgb (&inr, &ing, &inb);


  inr = CLAMP (inr, 0.0F, 1.0F);
  ing = CLAMP (ing, 0.0F, 1.0F);
  inb = CLAMP (inb, 0.0F, 1.0F);

  *outr = inr;
  *outg = ing;
  *outb = inb;
}
