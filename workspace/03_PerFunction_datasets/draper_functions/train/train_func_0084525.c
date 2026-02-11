copyport(port_list* head)
{
   port_list *new;

   if (!head) return NULL;
   new=newport();
   new->NEXT=copyport(head->NEXT);
   new->ABL=head->ABL;
   new->C=head->C;
   new->R=head->R;
   new->T=head->T;
   new->DIRECTION=head->DIRECTION;
   new->STABLE =head->STABLE;
   new->NEGATIV=head->NEGATIV;
   new->NAME=head->NAME;
   return new;
}
