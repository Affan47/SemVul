gt_ggc_mx_cgraph_node (void *x_p)
{
  struct cgraph_node * const x = (struct cgraph_node *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      gt_ggc_m_9tree_node ((*x).symbol.decl);
      gt_ggc_m_20vec_ipa_ref_t_va_gc_ ((*x).symbol.ref_list.references);
      gt_ggc_m_15symtab_node_def ((*x).symbol.same_comdat_group);
      gt_ggc_m_18lto_file_decl_data ((*x).symbol.lto_file_data);
      gt_ggc_m_15symtab_node_def ((*x).symbol.next);
      gt_ggc_m_15symtab_node_def ((*x).symbol.previous);
      gt_ggc_m_15symtab_node_def ((*x).symbol.next_sharing_asm_name);
      gt_ggc_m_15symtab_node_def ((*x).symbol.previous_sharing_asm_name);
      gt_ggc_m_11cgraph_edge ((*x).callees);
      gt_ggc_m_11cgraph_edge ((*x).callers);
      gt_ggc_m_11cgraph_edge ((*x).indirect_calls);
      {
        union symtab_node_def * const x0 =
          (symtab_node)((*x).origin);
        gt_ggc_m_15symtab_node_def (x0);
      }
      {
        union symtab_node_def * const x1 =
          (symtab_node)((*x).nested);
        gt_ggc_m_15symtab_node_def (x1);
      }
      {
        union symtab_node_def * const x2 =
          (symtab_node)((*x).next_nested);
        gt_ggc_m_15symtab_node_def (x2);
      }
      gt_ggc_m_11cgraph_node ((*x).next_sibling_clone);
      gt_ggc_m_11cgraph_node ((*x).prev_sibling_clone);
      gt_ggc_m_11cgraph_node ((*x).clones);
      gt_ggc_m_11cgraph_node ((*x).clone_of);
      gt_ggc_m_P11cgraph_edge4htab ((*x).call_site_hash);
      gt_ggc_m_9tree_node ((*x).former_clone_of);
      gt_ggc_m_11cgraph_node ((*x).global.inlined_to);
      gt_ggc_m_28vec_ipa_replace_map_p_va_gc_ ((*x).clone.tree_map);
      gt_ggc_m_15bitmap_head_def ((*x).clone.args_to_skip);
      gt_ggc_m_15bitmap_head_def ((*x).clone.combined_args_to_skip);
      gt_ggc_m_9tree_node ((*x).thunk.alias);
    }
}
