addCell_logic(befig_list* befig, chain_list* abl)
{
   cell_list* cell, *list;

   cell=addCell(befig);


   cell->ABL=build_reference(befig,cell->PORT,NULL,abl);

   put_arity_abl(cell->ABL);


   list=classCell(cell,LOGIC_CELLS);
   if (list) LOGIC_CELLS=list;

   return list?cell:NULL;
}
