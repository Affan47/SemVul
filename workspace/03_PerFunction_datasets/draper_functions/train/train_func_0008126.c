bcm5600_table_free(struct nm_16esw_data *d)
{
   struct bcm5600_table *table;
   m_uint32_t **array;
   int i;

   for(i=0;bcm5600_tables[i].name;i++) {
      table = &bcm5600_tables[i];
      array = (PTR_ADJUST(m_uint32_t **,d,table->offset));
      free(*array);


      *array = NULL;
   }
}
