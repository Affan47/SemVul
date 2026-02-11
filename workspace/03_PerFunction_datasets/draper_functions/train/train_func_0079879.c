cgi_standard_file()
{
  cgi_form form;
  char *template_filename, incoming_filename[BUFSIZ];
  int retval;

  template_filename = getenv("PATH_TRANSLATED");
  if (!template_filename || !(*template_filename))
    {
      cgi_redirect(CGI_NOPATH);
      return(1);
    }

  if (cgi_alloc_form(&form) ||
      cgi_parse_form(&form) ||
      cgi_template_fill(&form, template_filename))
    {
      cgi_output_failure(&form, "Form was not processed due to an error.");
      cgi_free_form(&form);
      return(1);
    }

  if (0 == cgi_parallel_fname(CGI_INFILE, incoming_filename, BUFSIZ))
    {
      if (!access(incoming_filename, W_OK))
	{
	  FILE *fp;
	  char buf[BUFSIZ];
	  int nbytes;
	  struct stat st;

#ifndef ENABLE_FILELINK
	  if (lstat(incoming_filename, &st))
	    {
	      form.errcond=1;
	      strcpy(form.errmsg, "500 Could not stat file");
	      cgi_concat_errno(form.errmsg);
	      strncpy(form.errinfo, incoming_filename, CGI_ERRMSG_MAX);
	      goto failure;
	    }
	  else
	    {
	      if (S_ISLNK(st.st_mode))
		{
		  form.errcond=1;
		  strcpy(form.errmsg, "500 File is symbolic link");
		  strncpy(form.errinfo, incoming_filename, CGI_ERRMSG_MAX);
		  goto failure;
		}
	      else
		if (st.st_nlink > 1)
		{
		  form.errcond=1;
		  strcpy(form.errmsg, "500 File is hard link");
		  strncpy(form.errinfo, incoming_filename, CGI_ERRMSG_MAX);
		  goto failure;
		}
	    }
#endif
	  rewind(form.tmpf);
	  fp = fopen(incoming_filename, "a");
	  if (fp)
	    {
	      do
		{
		  if ((nbytes = fread(buf, sizeof(char),
				      BUFSIZ, form.tmpf)) > 0)
		    fwrite(buf, sizeof(char), nbytes, fp);
		} while (nbytes == BUFSIZ);
	      if (fclose(fp))
		{
		  form.errcond=1;
		  strcpy(form.errmsg, "500 Write to file failed");
		  cgi_concat_errno(form.errmsg);
		  strncpy(form.errinfo, incoming_filename, CGI_ERRMSG_MAX);
		}
	    }
	  else
	    {
	      form.errcond=1;
	      strcpy(form.errmsg, "500 Could not append file");
	      cgi_concat_errno(form.errmsg);
	      strncpy(form.errinfo, incoming_filename, CGI_ERRMSG_MAX);
	    }
	}
      else
	{
	  form.errcond=1;
	  strcpy(form.errmsg, "500 No write access to file");
	  cgi_concat_errno(form.errmsg);
	  strncpy(form.errinfo, incoming_filename, CGI_ERRMSG_MAX);
	}
    }

#ifndef ENABLE_FILELINK
failure:
#endif
  if (form.errcond)
    cgi_output_failure(&form, "Form was not processed due to an error.");
  else
    cgi_output_success(&form, "The following information was written:");
  retval = form.errcond;
  cgi_free_form(&form);
  return retval;
}
