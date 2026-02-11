eio_grp_cancel (eio_req *grp)
{
  for (grp = grp->grp_first; grp; grp = grp->grp_next)
    eio_cancel (grp);
}
