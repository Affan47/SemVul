bc_free_code_attribute(JVM_CLASS *class, JVM_ATTRIBUTE *attr)
{
  if(!attr) {
    BAD_ARG();
    return;
  }

  bc_free_code(attr->attr.Code->code);

  if(attr->attr.Code->exception_table_length > 0)
    free(attr->attr.Code->exception_table);

  if((attr->attr.Code->attributes_count > 0) && (class != NULL))
    bc_free_attributes(class, attr->attr.Code->attributes);
  else
    dl_delete_list(attr->attr.Code->attributes);

  attr->attr.Code->attributes = NULL;

  free(attr->attr.Code);
  free(attr);
}
