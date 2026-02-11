set(Field *to,Field *from,bool save)
{
  if (to->type() == MYSQL_TYPE_NULL)
  {
    to_null_ptr=0;
    to_ptr=0;
    do_copy=do_skip;
    return;
  }
  from_field=from;
  to_field=to;
  from_ptr=from->ptr;
  from_length=from->pack_length();
  to_ptr=  to->ptr;
  to_length=to_field->pack_length();


  from_null_ptr=to_null_ptr=0;
  if (from->maybe_null())
  {
    from_null_ptr=	from->null_ptr;
    from_bit=		from->null_bit;
    if (to_field->real_maybe_null())
    {
      to_null_ptr=	to->null_ptr;
      to_bit=		to->null_bit;
      if (from_null_ptr)
	do_copy=	do_copy_null;
      else
      {
	null_row=	&from->table->null_row;
	do_copy=	do_outer_field_null;
      }
    }
    else
    {
      if (to_field->type() == MYSQL_TYPE_TIMESTAMP)
        do_copy= do_copy_timestamp;
      else if (to_field == to_field->table->next_number_field)
        do_copy= do_copy_next_number;
      else
        do_copy= do_copy_not_null;
    }
  }
  else if (to_field->real_maybe_null())
  {
    to_null_ptr=	to->null_ptr;
    to_bit=		to->null_bit;
    do_copy= do_copy_maybe_null;
  }
  else
   do_copy=0;

  if ((to->flags & BLOB_FLAG) && save)
    do_copy2= do_save_blob;
  else
    do_copy2= get_copy_func(to,from);
  if (!do_copy)
    do_copy=do_copy2;
}
