mailimf_single_fields_new(struct mailimf_fields * fields)
{
  struct mailimf_single_fields * single_fields;

  single_fields = malloc(sizeof(struct mailimf_single_fields));
  if (single_fields == NULL)
    goto err;

  mailimf_single_fields_init(single_fields, fields);

  return single_fields;

 err:
  return NULL;
}
