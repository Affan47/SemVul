addr_table_entry_do_hash (const void *x)
{
  const addr_table_entry *a = (const addr_table_entry *) x;
  switch (a->kind)
    {
      case ate_kind_rtx:
        return iterative_hash_rtx (a->addr.rtl, 0);
      case ate_kind_rtx_dtprel:
        return iterative_hash_rtx (a->addr.rtl, 1);
      case ate_kind_label:
        return htab_hash_string (a->addr.label);
      default:
        gcc_unreachable ();
    }
}
