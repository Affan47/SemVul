calculate_window (model, layer_num, dx, dy, nx, ny)
     rdsfig_list *model;
     int layer_num;
     long *dx, *dy, *nx, *ny;
{
   double tot_num_seg, nb_win, sq_win;
   rdsrec_list *rect;

   if (is_empty (model, layer_num))
      printf ("There is an error\n\n");
   for (rect = model->LAYERTAB[layer_num], tot_num_seg = 0; rect; rect = rect->NEXT, tot_num_seg++);
   if (tot_num_seg == 0)
   {
      *dx = *dy = *nx = *ny = 0;
   }
   else
   {
      nb_win = 2 * (double) sqrt ((double) tot_num_seg);
      sq_win = (double) sqrt ((double) nb_win);
      *nx = (long) sq_win + 1;
      *ny = *nx;
      *dx = model->BBOXTAB[layer_num]->DX / (*nx) + 1;
      *dy = model->BBOXTAB[layer_num]->DY / (*ny) + 1;
   }
}
