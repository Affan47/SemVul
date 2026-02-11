new_impl_pred_exec (int dir_fd, const char *pathname,
		    struct stat *stat_buf,
		    struct predicate *pred_ptr,
		    const char *prefix, size_t pfxlen)
{
  struct exec_val *execp = &pred_ptr->args.exec_vec;
  size_t len = strlen(pathname);

  (void) stat_buf;
  execp->dir_fd = dir_fd;
  if (execp->multiple)
    {


      bc_push_arg(&execp->ctl,
		  &execp->state,
		  pathname, len+1,
		  prefix, pfxlen,
		  0);


      state.execdirs_outstanding = true;


      return true;
    }
  else
    {
      int i;

      for (i=0; i<execp->num_args; ++i)
	{
	  bc_do_insert(&execp->ctl,
		       &execp->state,
		       execp->replace_vec[i],
		       strlen(execp->replace_vec[i]),
		       prefix, pfxlen,
		       pathname, len,
		       0);
	}


      return  execp->ctl.exec_callback(&execp->ctl,
					&execp->state);
    }
}
