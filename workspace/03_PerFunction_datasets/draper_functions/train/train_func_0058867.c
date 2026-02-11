nextxyz(win,add,ck)
plots *win;
INT add, ck;
{ plxyz *xyz;
  vari *v;
  varname vn;

  if (!add)
  { sprintf(vn,"_xyz%d",curwin);
    v = win->xyzs = createvar(vn,STSYSTEM,5,VXYZ);
    v->n = 0;
    win->xlab[0] = win->ylab[0] = win->zlab[0] = '\0';
  }
  else
    v = win->xyzs = growvar(win->xyzs,vlength(win->xyzs)+ck);

  xyz = (plxyz *)viptr(v,vlength(v));
  xyz->id = (vlength(v) << 4) + win->id;
  xyz->pch = 1;
  v->n++;
  return(xyz);
}
