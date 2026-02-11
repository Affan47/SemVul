create_tmp_field_from_field(THD *thd, Field *org_field,
                                   const char *name, TABLE *table,
                                   Item_field *item, uint convert_blob_length)
{
  Field *new_field;


  if (convert_blob_length && convert_blob_length <= Field_varstring::MAX_SIZE &&
      (org_field->flags & BLOB_FLAG))
    new_field= new Field_varstring(convert_blob_length,
                                   org_field->maybe_null(),
                                   org_field->field_name, table->s,
                                   org_field->charset());
  else
    new_field= org_field->new_field(thd->mem_root, table,
                                    table == org_field->table);
  if (new_field)
  {
    new_field->init(table);
    new_field->orig_table= org_field->orig_table;
    if (item)
      item->result_field= new_field;
    else
      new_field->field_name= name;
    new_field->flags|= (org_field->flags & NO_DEFAULT_VALUE_FLAG);
    if (org_field->maybe_null() || (item && item->maybe_null))
      new_field->flags&= ~NOT_NULL_FLAG;
    if (org_field->type() == MYSQL_TYPE_VAR_STRING ||
        org_field->type() == MYSQL_TYPE_VARCHAR)
      table->s->db_create_options|= HA_OPTION_PACK_RECORD;
    else if (org_field->type() == FIELD_TYPE_DOUBLE)
      ((Field_double *) new_field)->not_fixed= TRUE;
  }
  return new_field;
}
