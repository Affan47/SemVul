axis_transform_to_row_one_test (void)
{


  g_assert(0x00 == axis_transform_to_row_one(HO, 0x0000000000000000));
  g_assert(0xFF == axis_transform_to_row_one(HO, 0xFFFFFFFFFFFFFFFF));
  g_assert(0xFF == axis_transform_to_row_one(HO, 0x00000000000000FF));

  g_assert(0xFF == axis_transform_to_row_one(VE, 0x0101010101010101));
  g_assert(0x00 == axis_transform_to_row_one(VE, 0x1010101010101010));
  g_assert(0x88 == axis_transform_to_row_one(VE, 0x0100000001000000));

  g_assert(0x00 == axis_transform_to_row_one(DD, 0x0000000000000000));
  g_assert(0xFF == axis_transform_to_row_one(DD, 0xFFFFFFFFFFFFFFFF));
  g_assert(0xFF == axis_transform_to_row_one(DD, 0x8040201008040201));

  g_assert(0x00 == axis_transform_to_row_one(DU, 0x0000000000000000));
  g_assert(0xFF == axis_transform_to_row_one(DU, 0xFFFFFFFFFFFFFFFF));
  g_assert(0xFF == axis_transform_to_row_one(DU, 0x0102040810204080));
}
