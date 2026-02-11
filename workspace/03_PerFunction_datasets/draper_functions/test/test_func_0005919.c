cleanup_jpeg(jpeg *j)
{
   int i;
   for (i=0; i < j->s.img_n; ++i) {
      if (j->img_comp[i].data) {
         free(j->img_comp[i].raw_data);
         j->img_comp[i].data = NULL;
      }
      if (j->img_comp[i].linebuf) {
         free(j->img_comp[i].linebuf);
         j->img_comp[i].linebuf = NULL;
      }
   }
}
