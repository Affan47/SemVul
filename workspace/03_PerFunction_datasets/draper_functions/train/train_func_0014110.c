showOptionValues(void)
{
  int i;

  printf("Full command line is:\n`%s'\n", cmd.full_cmd_line);


  if( !cmd.numbitsP ) {
    printf("-b not found.\n");
  } else {
    printf("-b found:\n");
    if( !cmd.numbitsC ) {
      printf("  no values\n");
    } else {
      printf("  value = `%d'\n", cmd.numbits);
    }
  }


  if( !cmd.outfileP ) {
    printf("-o not found.\n");
  } else {
    printf("-o found:\n");
    if( !cmd.outfileC ) {
      printf("  no values\n");
    } else {
      printf("  value = `%s'\n", cmd.outfile);
    }
  }


  if( !cmd.numgbP ) {
    printf("-g not found.\n");
  } else {
    printf("-g found:\n");
    if( !cmd.numgbC ) {
      printf("  no values\n");
    } else {
      printf("  value = `%.40g'\n", cmd.numgb);
    }
  }
  if( !cmd.argc ) {
    printf("no remaining parameters in argv\n");
  } else {
    printf("argv =");
    for(i=0; i<cmd.argc; i++) {
      printf(" `%s'", cmd.argv[i]);
    }
    printf("\n");
  }
}
