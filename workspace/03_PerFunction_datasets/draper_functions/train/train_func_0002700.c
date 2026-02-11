ComputeField(bool changed) {

  FILE *fin;
  long  parentpid;
  long  childpid;
  int   status;
  int   ferror;


  if (AntennasInScene == true) {

    if ((TheAnts.ants[TheAnts.curr_ant].fieldComputed == false) ||
        (changed == true)){

      ferror = remove("output.nec");
      ferror = remove("input.nec");


      GenerateNECFile("input.nec");


      parentpid = getpid();
      if ((childpid = fork()) < 0) {
        fprintf(stderr,"Can't fork\n");
        exit(-2);
      }
      if (childpid == 0) {
        printf("Running NEC2 code...  please stand by...\n");
        execlp("nec2", "nec2", "input.nec", "output.nec", NULL);
        exit(-1);
      }
      else {
        if (wait(&status) != childpid) {
          fprintf(stderr,"Problem with child\n");
          exit(-3);
        }
      }


      fin  = fopen("output.nec", "rt");
      if(fin != NULL) {
        ParseFieldData(fin, &TheAnts.ants[TheAnts.curr_ant], true, true);
        fclose(fin);
      }
      else {
        fprintf(stderr, "Could Not Open File output.nec!!!\n");
        return;
      }


      printf("Field computation complete.\n");

      RFPowerDensityOn = true;
      FieldDataComputed = true;

    }

  }

}
