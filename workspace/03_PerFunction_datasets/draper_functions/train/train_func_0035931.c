print(void) const
{
   printf("if ( ");
   condition->print();
   printf(") ");

   then_statement->print();

   if (else_statement) {
      printf("else ");
      else_statement->print();
   }

}
