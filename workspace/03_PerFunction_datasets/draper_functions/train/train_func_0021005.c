parseCommandLine(int argc,char **argv){
  for (FXint i=0;i<argc;i++){
    if (comparecase(argv[i],"--disable-opengl")==0) {
      gui_show_opengl_coverview=false;
      }
    }
  }
