print(void) const
{
   if (this->is_unsized_array) {
      printf("[ ] ");
   }

   foreach_list_typed (ast_node, array_dimension, link, &this->array_dimensions) {
      printf("[ ");
      array_dimension->print();
      printf("] ");
   }
}
