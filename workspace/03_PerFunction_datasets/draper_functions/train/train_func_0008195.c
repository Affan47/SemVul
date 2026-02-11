NUDS_likobi0_NUDS (DS* u, DS* v)
    { var uintC u_len = u->len;
      var uintC v_len = v->len;
      if (u_len >= v_len)
        { if (!( addto_loop_lsp(v->LSDptr,u->LSDptr,v_len) ==0))
            { if (!( inc_loop_lsp(u->LSDptr lspop v_len,u_len-v_len) ==0))
                { lsprefnext(u->MSDptr) = 1; u->len++; }
        }   }
        else
        { u->MSDptr = copy_loop_lsp(v->LSDptr lspop u_len,u->LSDptr lspop u_len,v_len-u_len);
          u->len = v_len;
          if (!( addto_loop_lsp(v->LSDptr,u->LSDptr,u_len) ==0))
            { if (!( inc_loop_lsp(u->LSDptr lspop u_len,v_len-u_len) ==0))
                { lsprefnext(u->MSDptr) = 1; u->len++; }
        }   }
    }
