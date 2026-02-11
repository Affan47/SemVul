set_get_point (void)
{
  gcry_mpi_point_t point;
  gcry_mpi_t x, y, z;

  wherestr = "set_get_point";
  show ("checking point setting functions\n");

  point = gcry_mpi_point_new (0);
  x = gcry_mpi_set_ui (NULL, 17);
  y = gcry_mpi_set_ui (NULL, 42);
  z = gcry_mpi_set_ui (NULL, 11371);
  gcry_mpi_point_get (x, y, z, point);
  if (gcry_mpi_cmp_ui (x, 0)
      || gcry_mpi_cmp_ui (y, 0) || gcry_mpi_cmp_ui (z, 0))
    fail ("new point not initialized to (0,0,0)\n");
  gcry_mpi_point_snatch_get (x, y, z, point);
  point = NULL;
  if (gcry_mpi_cmp_ui (x, 0)
      || gcry_mpi_cmp_ui (y, 0) || gcry_mpi_cmp_ui (z, 0))
    fail ("snatch_get failed\n");
  gcry_mpi_release (x);
  gcry_mpi_release (y);
  gcry_mpi_release (z);

  point = gcry_mpi_point_new (0);
  x = gcry_mpi_set_ui (NULL, 17);
  y = gcry_mpi_set_ui (NULL, 42);
  z = gcry_mpi_set_ui (NULL, 11371);
  gcry_mpi_point_set (point, x, y, z);
  gcry_mpi_set_ui (x, 23);
  gcry_mpi_set_ui (y, 24);
  gcry_mpi_set_ui (z, 25);
  gcry_mpi_point_get (x, y, z, point);
  if (gcry_mpi_cmp_ui (x, 17)
      || gcry_mpi_cmp_ui (y, 42) || gcry_mpi_cmp_ui (z, 11371))
    fail ("point_set/point_get failed\n");
  gcry_mpi_point_snatch_set (point, x, y, z);
  x = gcry_mpi_new (0);
  y = gcry_mpi_new (0);
  z = gcry_mpi_new (0);
  gcry_mpi_point_get (x, y, z, point);
  if (gcry_mpi_cmp_ui (x, 17)
      || gcry_mpi_cmp_ui (y, 42) || gcry_mpi_cmp_ui (z, 11371))
    fail ("point_snatch_set/point_get failed\n");

  gcry_mpi_point_release (point);
  gcry_mpi_release (x);
  gcry_mpi_release (y);
  gcry_mpi_release (z);
}
