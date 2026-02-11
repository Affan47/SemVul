get_group_name(int ug)
{
   for (group_map_it it = group_map.begin();
        it != group_map.end();
        it++)
   {
      if (it->second.id == ug)
      {
         return(&it->second);
      }
   }
   return(NULL);
}
