ompi_mpi_cxx_comm_copy_attr_intercept(MPI_Comm comm, int keyval,
                                      void *extra_state,
                                      void *attribute_val_in,
                                      void *attribute_val_out, int *flag,
                                      MPI_Comm newcomm)
{
  int ret = 0;
  MPI::Comm::keyval_intercept_data_t *kid =
      (MPI::Comm::keyval_intercept_data_t*) extra_state;


  if (NULL != kid->c_copy_fn) {
      return kid->c_copy_fn(comm, keyval, kid->extra_state, attribute_val_in,
                            attribute_val_out, flag);
  }


  MPI::Intracomm intracomm;
  MPI::Intercomm intercomm;
  MPI::Graphcomm graphcomm;
  MPI::Cartcomm cartcomm;

  bool bflag = OPAL_INT_TO_BOOL(*flag);

  if (NULL != kid->cxx_copy_fn) {
      if (OMPI_COMM_IS_GRAPH(comm)) {
          graphcomm = MPI::Graphcomm(comm);
          ret = kid->cxx_copy_fn(graphcomm, keyval, kid->extra_state,
                                 attribute_val_in, attribute_val_out,
                                 bflag);
      } else if (OMPI_COMM_IS_CART(comm)) {
          cartcomm = MPI::Cartcomm(comm);
          ret = kid->cxx_copy_fn(cartcomm, keyval, kid->extra_state,
                                 attribute_val_in, attribute_val_out,
                                 bflag);
      } else if (OMPI_COMM_IS_INTRA(comm)) {
          intracomm = MPI::Intracomm(comm);
          ret = kid->cxx_copy_fn(intracomm, keyval, kid->extra_state,
                                 attribute_val_in, attribute_val_out,
                                 bflag);
      } else if (OMPI_COMM_IS_INTER(comm)) {
          intercomm = MPI::Intercomm(comm);
          ret = kid->cxx_copy_fn(intercomm, keyval, kid->extra_state,
                                 attribute_val_in, attribute_val_out,
                                 bflag);
      } else {
          ret = MPI::ERR_COMM;
      }
  } else {
      ret = MPI::ERR_OTHER;
  }

  *flag = (int)bflag;
  return ret;
}
