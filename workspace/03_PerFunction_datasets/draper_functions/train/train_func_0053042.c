prepare(uint32_t index, uint32_t *deferred_define) {
  uint32_t slot, frame, func, args, sym;
  int res;
  switch(TYPE(index)) {
    case T_SYM:
      res = find_symbol(STR_START(index), STR_LEN(index), &slot, &frame);
      if (res) {
        uint32_t var = store_var(slot, frame);
        return var;
      } else {
        printf("Undefined variable: "); dump_value(index, 0);
        putchar('\n');
        return 0;
      }
      break;
    case T_PAIR:
      func = CAR(index);
      args = CDR(index);
      if (!LIST_LIKE(args)) {
        printf("A dot pair but not a list in prepare()\n");
        return 0;
      };
      if (TYPE(func) == T_SYM) {
        if (IS_SYMBOL(func, "quote")) return index;

        if (IS_SYMBOL(func, "define")) {
          if (!check_list(args, 2, 1)) die("bad define/set! syntax");
          sym = CAR(args);
          if (TYPE(sym) != T_SYM) die("bad define syntax in prepare");
          add_symbol(STR_START(sym), STR_LEN(sym), &slot, &frame);
          uint32_t var = store_var(slot, frame);
          SET_CAR(args, var);
          if (deferred_define) {
            *deferred_define = CDR(args);
          } else {
            if (prepare_list(CDR(args)) == 0) return 0;
          }
          return index;
        }

        if (IS_SYMBOL(func, "lambda")) {


          add_symbol_table();
          uint32_t res = prepare_lambda(args);
          delete_symbol_table();
          return res;
        }


        if (IS_SYMBOL(func, "set!") || IS_SYMBOL(func, "if")) {

          uint32_t res = prepare_list(args);
          if (res == 0) return 0;
          return index;
        }
      }

      return prepare_list(index);
      break;
    default:
      break;
  }
  return index;
}
