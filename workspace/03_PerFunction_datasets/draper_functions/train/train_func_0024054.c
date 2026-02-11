outermost_loop_in_sese (sese region, basic_block bb)
{
  struct loop *nest;

  nest = bb->loop_father;
  while (loop_outer (nest)
	 && loop_in_sese_p (loop_outer (nest), region))
    nest = loop_outer (nest);

  return nest;
}
