add_row_set(lp_prob *p, waiting_row **wrows, int length)
{
   int i;
   row_data *row;
   add_waiting_rows(p, wrows, length);
   row = p->lp_data->rows + (p->lp_data->m - length);

   for (i=0; i<length; i++, row++){
      row->free = FALSE;
      row->cut = wrows[i]->cut;
      row->eff_cnt = 1;
      row->deletable = wrows[i]->cut->deletable;
      wrows[i]->cut = NULL;
   }
   free_waiting_rows(wrows, length);
}
