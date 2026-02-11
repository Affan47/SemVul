fport_end_input (SCM port, int offset)
{
  scm_t_fport *fp = SCM_FSTREAM (port);
  scm_t_port *pt = SCM_PTAB_ENTRY (port);

  offset += pt->read_end - pt->read_pos;

  if (offset > 0)
    {
      pt->read_pos = pt->read_end;


      if (lseek (fp->fdes, -offset, SEEK_CUR) == -1)
	scm_syserror ("fport_end_input");
    }
  pt->rw_active = SCM_PORT_NEITHER;
}
