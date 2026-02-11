_zone_count_get(void)
{
   int num = 0;
   E_Manager *m;
   Eina_List *ml;

   EINA_LIST_FOREACH(e_manager_list(), ml, m)
     {
        Eina_List *cl;
        E_Container *con;

        EINA_LIST_FOREACH(m->containers, cl, con)
          num += eina_list_count(con->zones);
     }
   return num;
}
