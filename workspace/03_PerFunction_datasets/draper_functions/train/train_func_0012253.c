eval_note(note_list* all_note, cell_list* cell, input_list *entry, int size, input_list* last_input)
{
   port_list* port;
   note_list* note;
   float latest=0, delay, R=0;
   int source_positiv, dest_positiv, cost;
   chain_list* portchain;


   if (size<=ABL_ARITY(cell->ABL)) return all_note;

   source_positiv=is_source_positiv(ABL_OPER(cell->ABL));
   dest_positiv=is_dest_positiv(ABL_OPER(cell->ABL),ABL_ARITY(cell->ABL));

   if (source_positiv==-1 || dest_positiv==-1) return all_note;


   for (note=all_note; note; note=note->NEXT) {
      if (note->ARITY==ABL_ARITY(cell->ABL)) break;
   }


   for (portchain=ABL_CDR(cell->ABL); portchain; portchain=portchain->NEXT) {
      port=(port_list*) ABL_ATOM_VALUE(ABL_CAR(portchain));
      delay=port->T ;
      delay+=source_positiv?entry->DELAY:entry->NEG_DELAY;

      delay+= port->C * (source_positiv?entry->R:entry->NEG_R);
      if (delay>latest) {latest=delay; R=port->R;}


      if (dest_positiv) {
         if (latest>=last_input->DELAY) return all_note;
      }
      else if (latest>=last_input->NEG_DELAY) return all_note;

      if (note) {

         if (dest_positiv) {
            if (latest>=note->DELAY) return all_note;
         }
         else if (latest>=note->NEG_DELAY) return all_note;
      }

      entry=entry->NEXT;
   }


   for (cost=1; entry; entry=entry->NEXT) {
      delay=dest_positiv?entry->DELAY:entry->NEG_DELAY;
      if (latest<=delay) break;
      cost++;
   }


   if (!entry) return all_note;


   if (!note) {
      note=newnote();
      note->NEXT=all_note;
      all_note=note;
      note->ARITY=ABL_ARITY(cell->ABL);
   }


   if (dest_positiv) {
      note->DELAY=latest;
      note->R=R;
      note->COST=cost;
      note->CELL=cell;
   }
   else {
      note->NEG_DELAY=latest;
      note->NEG_R=R;
      note->NEG_COST=cost;
      note->NEG_CELL=cell;
   }

   return all_note;
}
