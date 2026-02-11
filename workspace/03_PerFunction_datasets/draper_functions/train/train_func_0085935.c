test_index_tests__add(void)
{
   git_index *index;
   git_filebuf file = GIT_FILEBUF_INIT;
   git_repository *repo;
   git_index_entry *entry;
   git_oid id1;


   cl_git_pass(git_repository_init(&repo, "./myrepo", 0));


   cl_git_pass(git_repository_index(&index, repo));
   cl_assert(git_index_entrycount(index) == 0);


   cl_git_pass(git_futils_mkpath2file("myrepo/test.txt", 0777));
   cl_git_pass(git_filebuf_open(&file, "myrepo/test.txt", 0));
   cl_git_pass(git_filebuf_write(&file, "hey there\n", 10));
   cl_git_pass(git_filebuf_commit(&file, 0666));


   cl_git_pass(git_oid_fromstr(&id1, "a8233120f6ad708f843d861ce2b7228ec4e3dec6"));


   cl_git_pass(git_index_add(index, "test.txt", 0));


   cl_assert(git_index_entrycount(index) == 1);
   entry = git_index_get(index, 0);


   cl_assert(git_oid_cmp(&id1, &entry->oid) == 0);

   git_index_free(index);
   git_repository_free(repo);
}
