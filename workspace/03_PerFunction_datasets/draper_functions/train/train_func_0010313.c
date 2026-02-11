Typemaker2_Enum_free(TYPEMAKER2_ENUM *p_struct) {
  if (p_struct) {
    GWEN_LIST_FINI(TYPEMAKER2_ENUM, p_struct)

    free(p_struct->id);
    free(p_struct->prefix);
    free(p_struct->type);
    Typemaker2_Item_List_free(p_struct->items);
    free(p_struct->toStringFn);
    free(p_struct->fromStringFn);
    GWEN_FREE_OBJECT(p_struct);
  }
}
