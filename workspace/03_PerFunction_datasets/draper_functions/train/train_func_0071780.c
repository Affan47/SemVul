glp_read_graph(glp_graph *G, const char *fname)
{     glp_data *data;
      jmp_buf jump;
      int nv, na, i, j, k, ret;
      glp_erase_graph(G, G->v_size, G->a_size);
      xprintf("Reading graph from `%s'...\n", fname);
      data = glp_sdf_open_file(fname);
      if (data == NULL)
      {  ret = 1;
         goto done;
      }
      if (setjmp(jump))
      {  ret = 1;
         goto done;
      }
      glp_sdf_set_jump(data, jump);
      nv = glp_sdf_read_int(data);
      if (nv < 0)
         glp_sdf_error(data, "invalid number of vertices\n");
      na = glp_sdf_read_int(data);
      if (na < 0)
         glp_sdf_error(data, "invalid number of arcs\n");
      xprintf("Graph has %d vert%s and %d arc%s\n",
         nv, nv == 1 ? "ex" : "ices", na, na == 1 ? "" : "s");
      if (nv > 0) glp_add_vertices(G, nv);
      for (k = 1; k <= na; k++)
      {  i = glp_sdf_read_int(data);
         if (!(1 <= i && i <= nv))
            glp_sdf_error(data, "tail vertex number out of range\n");
         j = glp_sdf_read_int(data);
         if (!(1 <= j && j <= nv))
            glp_sdf_error(data, "head vertex number out of range\n");
         glp_add_arc(G, i, j);
      }
      xprintf("%d lines were read\n", glp_sdf_line(data));
      ret = 0;
done: if (data != NULL) glp_sdf_close_file(data);
      return ret;
}
