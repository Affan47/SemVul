material_clear() {

   if (Material->table != NULL) {
      memset(Material->table,0,Material->size*sizeof(entry_t));
   }

   Material->used = 0;
   Material->read_nb = 0;
   Material->read_hit = 0;
   Material->write_nb = 0;
   Material->write_collision = 0;
}
