test_index_tests__gitgit_index(void)
{
   git_index *index;

   cl_git_pass(git_index_open(&index, TEST_INDEX2_PATH));
   cl_assert(index->on_disk);

   cl_assert(git_index_entrycount(index) == index_entry_count_2);
   cl_assert(index->entries.sorted);
   cl_assert(index->tree != NULL);

   git_index_free(index);
}
