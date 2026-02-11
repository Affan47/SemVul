transpose_get_send_block(transpose_mpi_plan p, int step,
			      int *block_y_start, int *block_ny)
{
     if (p->local_nx > 0) {
	  *block_y_start =
	       p->send_block_size / p->local_nx * p->exchange[step].block_num;
	  *block_ny = p->exchange[step].send_size / p->local_nx;
     }
     else {
	  *block_y_start = 0;
	  *block_ny = 0;
     }
}
