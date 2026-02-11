get_arrow_sprite(const struct tileset *t,
                                enum arrow_type arrow)
{
  fc_assert_ret_val(arrow >= 0 && arrow < ARROW_LAST, NULL);

  return t->sprites.arrow[arrow];
}
