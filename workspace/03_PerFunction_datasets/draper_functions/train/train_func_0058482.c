glp_check_asnprob(glp_graph *G, int v_set)
{     glp_vertex *v;
      int i, k, ret = 0;
      if (v_set >= 0 && v_set > G->v_size - (int)sizeof(int))
         xerror("glp_check_asnprob: v_set = %d; invalid offset\n",
            v_set);
      for (i = 1; i <= G->nv; i++)
      {  v = G->v[i];
         if (v_set >= 0)
         {  memcpy(&k, (char *)v->data + v_set, sizeof(int));
            if (k == 0)
            {  if (v->in != NULL)
               {  ret = 1;
                  break;
               }
            }
            else if (k == 1)
            {  if (v->out != NULL)
               {  ret = 2;
                  break;
               }
            }
            else
            {  ret = 3;
               break;
            }
         }
         else
         {  if (v->in != NULL && v->out != NULL)
            {  ret = 4;
               break;
            }
         }
      }
      return ret;
}
