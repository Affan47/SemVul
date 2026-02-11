transpose_mpi_get_local_storage_size(int nx, int ny,
					 int my_pe, int n_pes)
{
     int local_nx, local_ny, local_x_start, local_y_start;

     transpose_mpi_get_local_size(nx,my_pe,n_pes,&local_nx,&local_x_start);
     transpose_mpi_get_local_size(ny,my_pe,n_pes,&local_ny,&local_y_start);

     return MAX2(1, MAX2(local_nx*ny, nx*local_ny));
}
