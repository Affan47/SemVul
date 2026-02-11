receive (GfsBoundary * bb,
		     FttTraverseFlags flags,
		     gint max_depth)
{
  GfsBoundaryPeriodic * boundary = GFS_BOUNDARY_PERIODIC (bb);
  GfsBoundaryMpi * mpi = GFS_BOUNDARY_MPI (bb);
  GfsDomain * domain = gfs_box_domain (bb->box);
  MPI_Status status;
  gint count;

  if (domain->pid < 0)
    return;

#ifdef PROFILE_MPI
  gdouble start, end;

  start = MPI_Wtime ();
#endif

  if (GFS_BOUNDARY (boundary)->type == GFS_BOUNDARY_MATCH_VARIABLE) {
#ifdef DEBUG
fprintf (DEBUG, "%d wait on %d with tag %d for match variable size\n",
	 gfs_box_domain (bb->box)->pid,
	 mpi->process,
	 MATCHING_TAG (GFS_BOUNDARY (boundary)));
fflush (DEBUG);
#endif
    MPI_Recv (&boundary->rcvcount, 1, MPI_UNSIGNED,
	      mpi->process,
	      MATCHING_TAG (GFS_BOUNDARY (boundary)),
	      mpi->comm,
	      &status);
#ifdef PROFILE_MPI
    end = MPI_Wtime ();
    gts_range_add_value (&domain->mpi_wait, end - start);
    start = MPI_Wtime ();
#endif
    if (boundary->rcvcount > boundary->rcvbuf->len)
      g_array_set_size (boundary->rcvbuf, boundary->rcvcount);
  }
  else
    boundary->rcvcount = boundary->sndcount;
#ifdef DEBUG
  fprintf (DEBUG, "%d wait on %d with tag %d\n",
	   gfs_box_domain (bb->box)->pid,
	   mpi->process,
	   MATCHING_TAG (GFS_BOUNDARY (boundary)));
fflush (DEBUG);
#endif
  g_assert (boundary->rcvcount <= boundary->rcvbuf->len);
  MPI_Recv (boundary->rcvbuf->data,
	    boundary->rcvcount,
	    MPI_DOUBLE,
	    mpi->process,
	    MATCHING_TAG (GFS_BOUNDARY (boundary)),
	    mpi->comm,
	    &status);
  MPI_Get_count (&status, MPI_DOUBLE, &count);
#ifdef DEBUG
  fprintf (DEBUG, "src: %d tag: %d error: %d\n",
	   status.MPI_SOURCE, status.MPI_TAG, status.MPI_ERROR);
  if (count == MPI_UNDEFINED) {
    fprintf (DEBUG, "%d on tag %d: count is undefined!\n",
	     gfs_box_domain (bb->box)->pid,
	     MATCHING_TAG (GFS_BOUNDARY (boundary)));
    g_assert_not_reached ();
  }
  else if (count != boundary->rcvcount) {
    fprintf (DEBUG, "%d on tag %d: count = %d boundary->rcvcount = %d\n",
	     gfs_box_domain (bb->box)->pid,
	     MATCHING_TAG (GFS_BOUNDARY (boundary)),
	     count, boundary->rcvcount);
    g_assert_not_reached ();
  }
#else
  g_assert (count == boundary->rcvcount);
#endif

#ifdef PROFILE_MPI
  end = MPI_Wtime ();
  gts_range_add_value (&domain->mpi_wait, end - start);
#endif

  (* gfs_boundary_periodic_class ()->receive) (bb, flags, max_depth);
}
