assign_locations()
{

   qsort(this->matches, this->num_matches, sizeof(*this->matches),
         &varying_matches::match_comparator);

   unsigned generic_location = 0;

   for (unsigned i = 0; i < this->num_matches; i++) {


      if (i > 0 &&
          this->matches[i - 1].packing_class
          != this->matches[i].packing_class) {
         generic_location = ALIGN(generic_location, 4);
      }

      this->matches[i].generic_location = generic_location;

      generic_location += this->matches[i].num_components;
   }

   return (generic_location + 3) / 4;
}
