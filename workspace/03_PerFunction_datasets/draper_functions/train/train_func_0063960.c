glp_write_graph(glp_graph *G, const char *fname)
{     XFILE *fp;
      glp_vertex *v;
      glp_arc *a;
      int i, count, ret;
      xprintf("Writing graph to `%s'...\n", fname);
      fp = xfopen(fname, "w"), count = 0;
      if (fp == NULL)
      {  xprintf("Unable to create `%s' - %s\n", fname, xerrmsg());
         ret = 1;
         goto done;
      }
      xfprintf(fp, "%d %d\n", G->nv, G->na), count++;
      for (i = 1; i <= G->nv; i++)
      {  v = G->v[i];
         for (a = v->out; a != NULL; a = a->t_next)
            xfprintf(fp, "%d %d\n", a->tail->i, a->head->i), count++;
      }
      xfflush(fp);
      if (xferror(fp))
      {  xprintf("Write error on `%s' - %s\n", fname, xerrmsg());
         ret = 1;
         goto done;
      }
      xprintf("%d lines were written\n", count);
      ret = 0;
done: if (fp != NULL) xfclose(fp);
      return ret;
}
