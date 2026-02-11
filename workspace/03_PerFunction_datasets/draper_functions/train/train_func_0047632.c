SetUp()
{
  ASSERT_EQ(0, cluster.ioctx_create(pool_name.c_str(), ioctx));
  ns = get_temp_pool_name();
  ioctx.set_namespace(ns);
  ASSERT_TRUE(ioctx.pool_requires_alignment());
  alignment = ioctx.pool_required_alignment();
  ASSERT_NE((unsigned)0, alignment);
}
