dirtest(void)
{
  printf(stdout, "mkdir test\n");

  if(mkdir("dir0") < 0) {
    printf(stdout, "mkdir failed\n");
    exit();
  }

  if(chdir("dir0") < 0) {
    printf(stdout, "chdir dir0 failed\n");
    exit();
  }

  if(chdir("..") < 0) {
    printf(stdout, "chdir .. failed\n");
    exit();
  }

  if(unlink("dir0") < 0) {
    printf(stdout, "unlink dir0 failed\n");
    exit();
  }
  printf(stdout, "mkdir test\n");
}
