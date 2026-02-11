SaveConfig(void) {
  FILE *config_file;
  unsigned i;
  char filename[100];
  char msg[200];


  sprintf(filename,"%s/.%s",getenv("FVWM_USERDIR"),module->name);
  config_file = fopen(filename,"w");
  if (config_file == NULL) {
    sprintf(msg,
	    "%s: Open config file <%s> for write failed. \
Save not done! Error\n",
	    module->name, filename);
    perror(msg);
    return;
  }
  fprintf(config_file,"# This file was created by %s\n\n",module->name);
  for (i=0; i < NUM_EFFECTS; i++) {
    if (effects[i].function == Animate.resize) {
      fprintf(config_file,"*%s: Effect %s\n",module->name,effects[i].name);
      break;
    }
  }
  fprintf(config_file,"*%s: Iterations %d\n",module->name,Animate.iterations);
  fprintf(config_file,"*%s: Width %d\n",module->name,Animate.width);
  fprintf(config_file,"*%s: Twist %f\n",module->name,Animate.twist);
  fprintf(config_file,"*%s: Delay %d\n",module->name,Animate.delay);
  if (Animate.color) {
    fprintf(config_file,"*%s: Color %s\n",module->name,Animate.color);
  }

  fclose(config_file);
}
