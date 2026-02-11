add_new_rows_to_waiting_rows(lp_prob *p, waiting_row **new_rows,
				  int new_row_num)
{
   new_row_num = compute_violations(p, new_row_num, new_rows);

   if (new_row_num > 0){


      REALLOC(p->waiting_rows, waiting_row *, p->waiting_rows_size,
	      p->waiting_row_num + new_row_num, BB_BUNCH);
      memcpy((p->waiting_rows + p->waiting_row_num), new_rows,
	     new_row_num * sizeof(waiting_row *));
      p->waiting_row_num += new_row_num;
   }
}
