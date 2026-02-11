clarion_free_handle (ClarionHandle *cl)
{
  int i, j;
  ClarionPicDesc *clp = cl->clm.clp;
  ClarionKeyDesc *clk = cl->clm.clk;
  ClarionFieldDesc *clfd = cl->clm.clfd;

  for (i = 0; i < cl->clm.clh->numbkeys; i++)
    {
      for (j = 0; j < clk[i].numcomps; j++)
	{
	  if (clk[i].keypart[j].subpart != NULL)
	    free(clk[i].keypart[j].subpart);
	}

      free(clk[i].keypart);
    }
  free(clk);

  if (cl->clm.clh->numpics > 0)
    {
      for (i = 0; i < cl->clm.clh->numpics; i++)
	{
	  if (clp[i].picstr)
	    free(clp[i].picstr);
	}
      free(clp);
    }

  for (i = 0; i < cl->clm.clh->numflds; i++)
    {
      if (clfd[i].arr != NULL)
	{
	  for (j = 0; j < clfd[i].nbarrs; j++)
	    {
	      free(clfd[i].arr[j].part);
	    }
	  free(clfd[i].arr);
	}
    }
  free(clfd);

  free(cl->clm.clh);

  free(cl->datfile);

  if (cl->memfile != NULL)
    free(cl->memfile);

  if (cl->charset != NULL)
    free(cl->charset);
}
