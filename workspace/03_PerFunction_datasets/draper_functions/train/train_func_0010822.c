process_arithmetic_op(HSCPRC * hp, EXPSTR * result, BYTE op, STRPTR str1, STRPTR str2) {
   BOOL result_set = TRUE;
   LONG int1 = 0;
   LONG int2 = 0;
   LONG intr = 0;


   result_set = stroptol(hp, &int1, str1);
   result_set &= stroptol(hp, &int2, str2);

   if ((int2 == 0) && ((op == OP_DIV) || (op == OP_MOD))) {

      hsc_message(hp, MSG_ARITHMETIC_ERROR,
            "arithmetic error: division by zero");
      result_set = FALSE;
   } else {

      switch (op) {
         case OP_ADD:
            intr = int1 + int2;
            break;
         case OP_SUB:
            intr = int1 - int2;
            break;
         case OP_MUL:
            intr = int1 * int2;
            break;
         case OP_DIV:
            intr = int1 / int2;
            break;
         case OP_MOD:
            intr = int1 % int2;
            break;
         default:
            panic("unknown arithmetic operator");
            break;
      }
   }


   if (result_set) {
      STRARR buf[20];
      sprintf(buf, "%ld", intr);
      set_estr(result, buf);
   }
   return result_set;
}
