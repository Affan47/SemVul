gt_ggc_mx_answer (void *x_p)
{
  struct answer * const x = (struct answer *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      {
        size_t l0 = (size_t)(((*x)).count);
        gt_ggc_m_6answer ((*x).next);
        {
          size_t i0;
          for (i0 = 0; i0 != l0; i0++) {
            switch (cpp_token_val_index (&((*x).first[i0])))
              {
              case CPP_TOKEN_FLD_NODE:
                {
                  union tree_node * const x1 =
                    ((*x).first[i0].val.node.node) ? HT_IDENT_TO_GCC_IDENT (HT_NODE (((*x).first[i0].val.node.node))) : NULL;
                  gt_ggc_m_9tree_node (x1);
                }
                break;
              case CPP_TOKEN_FLD_SOURCE:
                gt_ggc_m_9cpp_token ((*x).first[i0].val.source);
                break;
              case CPP_TOKEN_FLD_STR:
                gt_ggc_m_S ((*x).first[i0].val.str.text);
                break;
              case CPP_TOKEN_FLD_ARG_NO:
                break;
              case CPP_TOKEN_FLD_TOKEN_NO:
                break;
              case CPP_TOKEN_FLD_PRAGMA:
                break;
              default:
                break;
              }
          }
        }
      }
    }
}
