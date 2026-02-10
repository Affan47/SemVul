exec_read(struct exec_info *info)
{
  int ret=G10ERR_GENERAL;

  fclose(info->tochild);
  info->tochild=NULL;

  if(info->flags.use_temp_files)
    {
      if(DBG_EXTPROG)
	log_debug("system() command is %s\n",info->command);

#if defined (_WIN32)
      info->progreturn=win_system(info->command);
#else
      info->progreturn=system(info->command);
#endif

      if(info->progreturn==-1)
	{
	  log_error(_("system error while calling external program: %s\n"),
		    strerror(errno));
	  info->progreturn=127;
	  goto fail;
	}

#if defined(WIFEXITED) && defined(WEXITSTATUS)
      if(WIFEXITED(info->progreturn))
	info->progreturn=WEXITSTATUS(info->progreturn);
      else
	{
	  log_error(_("unnatural exit of external program\n"));
	  info->progreturn=127;
	  goto fail;
	}
#else

      info->progreturn = (info->progreturn & 0xff00) >> 8;
#endif


      if(info->progreturn==127)
	{
	  log_error(_("unable to execute external program\n"));
	  goto fail;
	}

      if(!info->flags.writeonly)
	{
	  info->fromchild=iobuf_open(info->tempfile_out);
          if (info->fromchild
              && is_secured_file (iobuf_get_fd (info->fromchild)))
            {
              iobuf_close (info->fromchild);
              info->fromchild = NULL;
              errno = EPERM;
            }
	  if(info->fromchild==NULL)
	    {
	      log_error(_("unable to read external program response: %s\n"),
			strerror(errno));
	      ret=G10ERR_READ_FILE;
	      goto fail;
	    }


	  iobuf_ioctl(info->fromchild,3,1,NULL);
	}
    }

  ret=0;

 fail:
  return ret;
}
