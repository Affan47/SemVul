structure_subtypep(object x, object y)
{ if (x==y) return 1;
  if (type_of(x)!= t_structure
      || type_of(y)!=t_structure)
    FEerror("bad call to structure_subtypep",0);
  {if (S_DATA(y)->included == Cnil) return 0;
   while ((x=S_DATA(x)->includes) != Cnil)
     { if (x==y) return 1;}
   return 0;
 }}
