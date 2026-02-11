lto_max_map (void)
{
  symtab_node node;
  ltrans_partition partition;
  int npartitions = 0;

  FOR_EACH_SYMBOL (node)
    {
      if (get_symbol_class (node) != SYMBOL_PARTITION
	  || symbol_partitioned_p (node))
	continue;
      partition = new_partition (symtab_node_asm_name (node));
      add_symbol_to_partition (partition, (symtab_node) node);
      npartitions++;
    }
  if (!npartitions)
    new_partition ("empty");
}
